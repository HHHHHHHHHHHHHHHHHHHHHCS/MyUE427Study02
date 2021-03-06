// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "MainPlayer.generated.h"

UCLASS(config=Game)
class AMainPlayer : public ACharacter
{
	GENERATED_BODY()

	/** Camera boom positioning the camera behind the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* FollowCamera;

	/** Camera boom positioning the camera behind the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* cameraHead;

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* perspectiveCamera;

public:
	AMainPlayer();

	/** Base turn rate, in deg/sec. Other scaling may affect final turn rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera)
	float BaseTurnRate;

	/** Base look up/down rate, in deg/sec. Other scaling may affect final rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera)
	float BaseLookUpRate;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Player|Status", meta = (ClampMin=0))
	float nowHP;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Player|Status", meta = (ClampMin=0))
	float maxHP;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Player|Status", meta = (ClampMin=0))
	float nowEnergy;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Player|Status", meta = (ClampMin=0))
	float runEnergy;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Player|Status", meta = (ClampMin=0))
	float walkSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Player|Status", meta = (ClampMin=0))
	float runSpeed;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Player|Status", meta = (ClampMin=0))
	float maxEnergy;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Player|Status", meta = (ClampMin=0))
	float nowHungry;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Player|Status", meta = (ClampMin=0))
	float maxHungry;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Player|Status", meta = (ClampMin=0))
	float hungrySpeed;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Player|Status", meta = (ClampMin=0))
	float nowSaturation;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Player|Status", meta = (ClampMin=0))
	float maxSaturation;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Player|Status", meta = (ClampMin=0))
	float saturationSpeed;

private:
	bool isDash;

protected:
	/** Resets HMD orientation in VR. */
	void OnResetVR();

	/** Called for forwards/backward input */
	void MoveForward(float Value);

	/** Called for side to side input */
	void MoveRight(float Value);

	/** 
	 * Called via input to turn at a given rate. 
	 * @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	 */
	void TurnAtRate(float Rate);

	/**
	 * Called via input to turn look up/down at a given rate. 
	 * @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	 */
	void LookUpAtRate(float Rate);

	/** Handler for when a touch input begins. */
	void TouchStarted(ETouchIndex::Type FingerIndex, FVector Location);

	/** Handler for when a touch input stops. */
	void TouchStopped(ETouchIndex::Type FingerIndex, FVector Location);

	virtual void Tick(float DeltaSeconds) override;

	void UpdatePlayerStatus(float deltaSeconds);

	virtual float MyTakeDamage(float damageAmount, AActor* damageCauser);

protected:
	// APawn interface
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	// End of APawn interface

public:
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	/** Returns FollowCamera subobject **/
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }

	UFUNCTION()
	void OnChangePlayerPerspective();

	UFUNCTION()
	void OnPressedDash();

	UFUNCTION()
	void OnReleasedDash();

	void AddHungry(float val);

	void AddSaturation(float val);

	void RayCast();
};
