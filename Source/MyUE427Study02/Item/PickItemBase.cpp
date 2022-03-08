// Fill out your copyright notice in the Description page of Project Settings.


#include "PickItemBase.h"

#include "MyUE427Study02/Player/MainPlayer.h"

// Sets default values
APickItemBase::APickItemBase()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	itemCollision = CreateDefaultSubobject<USphereComponent>(TEXT("ItemCollision"));
	itemCollision->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	itemCollision->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Overlap);
	itemCollision->SetSphereRadius(64.0f);
	SetRootComponent(itemCollision);

	itemMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ItemMesh"));
	itemMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	itemMesh->SetupAttachment(itemCollision);
}

// Called when the game starts or when spawned
void APickItemBase::BeginPlay()
{
	Super::BeginPlay();

	itemCollision->OnComponentBeginOverlap.AddDynamic(this, &APickItemBase::OnBeginOverlap);
	itemCollision->OnComponentEndOverlap.AddDynamic(this, &APickItemBase::OnEndOverlap);
}


// Called every frame
void APickItemBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void APickItemBase::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
                                   UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
                                   const FHitResult& SweepResult)
{
	AMainPlayer* mainPlayer = Cast<AMainPlayer>(OtherActor);
	if (mainPlayer)
	{
		DoBeginOverlap(mainPlayer);

		itemCollision->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		Destroy();
	}
}

void APickItemBase::DoBeginOverlap(AMainPlayer* mainPlayer)
{
}

void APickItemBase::OnEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
                                 UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	AMainPlayer* mainPlayer = Cast<AMainPlayer>(OtherActor);
	if (mainPlayer)
	{
		DoEndOverlap(mainPlayer);
	}
}

void APickItemBase::DoEndOverlap(AMainPlayer* mainPlayer)
{
}
