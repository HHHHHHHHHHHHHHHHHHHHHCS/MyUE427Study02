// Copyright Epic Games, Inc. All Rights Reserved.

#include "MainPlayer.h"
#include "HeadMountedDisplayFunctionLibrary.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/SpringArmComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"

//////////////////////////////////////////////////////////////////////////
// AMyUE427Study02Character

AMainPlayer::AMainPlayer()
{
	PrimaryActorTick.bCanEverTick = true;

	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	// set our turn rates for input
	BaseTurnRate = 45.f;
	BaseLookUpRate = 45.f;

	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input...	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 540.0f, 0.0f); // ...at this rotation rate
	GetCharacterMovement()->JumpZVelocity = 600.f;
	GetCharacterMovement()->AirControl = 0.2f;

	// Create a camera boom (pulls in towards the player if there is a collision)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 300.0f; // The camera follows at this distance behind the character	
	CameraBoom->bUsePawnControlRotation = true; // Rotate the arm based on the controller

	// Create a follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	// Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	FollowCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

	cameraHead = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraHead"));
	cameraHead->SetupAttachment(GetMesh(), "head");
	cameraHead->AddRelativeLocation(FVector(0, 10, 0));
	cameraHead->TargetArmLength = 0.0f;
	cameraHead->bUsePawnControlRotation = true;
	cameraHead->SetWorldRotation(FRotator(-90, 0, 90));

	perspectiveCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("PerspectiveCamera"));
	perspectiveCamera->SetupAttachment(cameraHead, USpringArmComponent::SocketName);
	perspectiveCamera->bUsePawnControlRotation = false;
	perspectiveCamera->SetAutoActivate(false);

	// Note: The skeletal mesh and anim blueprint references on the Mesh component (inherited from Character) 
	// are set in the derived blueprint asset named MyCharacter (to avoid direct content references in C++)

	maxHP = 100.0f;
	nowHP = maxHP;

	maxEnergy = 100.0f;
	nowEnergy = maxEnergy;
	runEnergy = 10.0f;
	walkSpeed = 600.0f;
	runSpeed = 1200.0f;
	OnReleasedDash();

	maxHungry = 100.0f;
	nowHungry = maxHungry;
	hungrySpeed = 1.0f;

	maxSaturation = 100.0f;
	nowSaturation = maxSaturation;
	saturationSpeed = 1.0f;
}

//////////////////////////////////////////////////////////////////////////
// Input

#pragma region Input

void AMainPlayer::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	// Set up gameplay key bindings
	check(PlayerInputComponent);
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);

	PlayerInputComponent->BindAxis("MoveForward", this, &AMainPlayer::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AMainPlayer::MoveRight);

	// We have 2 versions of the rotation bindings to handle different kinds of devices differently
	// "turn" handles devices that provide an absolute delta, such as a mouse.
	// "turnrate" is for devices that we choose to treat as a rate of change, such as an analog joystick
	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("TurnRate", this, &AMainPlayer::TurnAtRate);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("LookUpRate", this, &AMainPlayer::LookUpAtRate);

	// handle touch devices
	PlayerInputComponent->BindTouch(IE_Pressed, this, &AMainPlayer::TouchStarted);
	PlayerInputComponent->BindTouch(IE_Released, this, &AMainPlayer::TouchStopped);

	// VR headset functionality
	PlayerInputComponent->BindAction("ResetVR", IE_Pressed, this, &AMainPlayer::OnResetVR);

	PlayerInputComponent->BindAction("ChangePlayerPerspective", IE_Pressed, this,
	                                 &AMainPlayer::OnChangePlayerPerspective);

	PlayerInputComponent->BindAction("Dash", IE_Pressed, this,
	                                 &AMainPlayer::OnPressedDash);
	PlayerInputComponent->BindAction("Dash", IE_Released, this,
	                                 &AMainPlayer::OnReleasedDash);
}

void AMainPlayer::OnResetVR()
{
	// If MyUE427Study02 is added to a project via 'Add Feature' in the Unreal Editor the dependency on HeadMountedDisplay in MyUE427Study02.Build.cs is not automatically propagated
	// and a linker error will result.
	// You will need to either:
	//		Add "HeadMountedDisplay" to [YourProject].Build.cs PublicDependencyModuleNames in order to build successfully (appropriate if supporting VR).
	// or:
	//		Comment or delete the call to ResetOrientationAndPosition below (appropriate if not supporting VR)
	UHeadMountedDisplayFunctionLibrary::ResetOrientationAndPosition();
}

void AMainPlayer::TouchStarted(ETouchIndex::Type FingerIndex, FVector Location)
{
	Jump();
}

void AMainPlayer::TouchStopped(ETouchIndex::Type FingerIndex, FVector Location)
{
	StopJumping();
}

void AMainPlayer::TurnAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerYawInput(Rate * BaseTurnRate * GetWorld()->GetDeltaSeconds());
}

void AMainPlayer::LookUpAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerPitchInput(Rate * BaseLookUpRate * GetWorld()->GetDeltaSeconds());
}

void AMainPlayer::MoveForward(float Value)
{
	if ((Controller != nullptr) && (Value != 0.0f))
	{
		// find out which way is forward
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		AddMovementInput(Direction, Value);
	}
}

void AMainPlayer::MoveRight(float Value)
{
	if ((Controller != nullptr) && (Value != 0.0f))
	{
		// find out which way is right
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get right vector 
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		// add movement in that direction
		AddMovementInput(Direction, Value);
	}
}

#pragma endregion

void AMainPlayer::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	UpdatePlayerStatus(DeltaSeconds);
}

void AMainPlayer::UpdatePlayerStatus(float deltaSeconds)
{
	const float speed = GetVelocity().Size();

	if (isDash && speed > walkSpeed)
	{
		if (nowEnergy <= 0)
		{
			OnReleasedDash();
		}
		nowEnergy = FMath::Max(0.0f, nowEnergy - runEnergy * deltaSeconds);
	}
	else
	{
		nowEnergy = FMath::Min(maxEnergy, nowEnergy + runEnergy * deltaSeconds);
	}

	nowHungry -= hungrySpeed * deltaSeconds;
	const float tempHungry = nowHungry;
	nowHungry = FMath::Clamp(nowHungry, 0.0f, maxHungry);
	if (tempHungry < 0)
	{
		this->MyTakeDamage(-tempHungry, nullptr);
	}

	nowSaturation -= saturationSpeed * deltaSeconds;
	const float tempSaturation = nowSaturation;
	nowSaturation = FMath::Clamp(nowSaturation, 0.0f, maxSaturation);
	if (tempSaturation < 0)
	{
		this->MyTakeDamage(-tempSaturation, nullptr);
	}
}


float AMainPlayer::MyTakeDamage(float damageAmount, AActor* damageCauser)
{
	if (damageAmount < 0)
	{
		UKismetSystemLibrary::PrintString(this, "MyTakeDamage damageAmount < 0");
		return nowHP;
	}

	nowHP = FMath::Clamp(nowHP - damageAmount, 0.0f, maxHP);
	if (nowHP <= 0)
	{
	}

	return nowHP;
}

void AMainPlayer::OnChangePlayerPerspective()
{
	FollowCamera->ToggleActive();
	perspectiveCamera->ToggleActive();
	bUseControllerRotationYaw = !bUseControllerRotationYaw;
}

void AMainPlayer::OnPressedDash()
{
	if (nowEnergy <= 0)
	{
		OnReleasedDash();
		return;
	}

	isDash = true;
	GetCharacterMovement()->MaxWalkSpeed = runSpeed;
}

void AMainPlayer::OnReleasedDash()
{
	isDash = false;
	GetCharacterMovement()->MaxWalkSpeed = walkSpeed;
}
