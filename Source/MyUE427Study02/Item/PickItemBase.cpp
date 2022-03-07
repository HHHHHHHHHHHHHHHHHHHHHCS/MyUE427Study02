// Fill out your copyright notice in the Description page of Project Settings.


#include "PickItemBase.h"

#include "MyUE427Study02/Player/MainPlayer.h"

// Sets default values
APickItemBase::APickItemBase()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	itemMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ItemMesh"));
	itemMesh->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	itemMesh->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Overlap);
	itemMesh->SetupAttachment(GetRootComponent());
}

// Called when the game starts or when spawned
void APickItemBase::BeginPlay()
{
	Super::BeginPlay();

	itemMesh->OnComponentBeginOverlap.AddDynamic(this, &APickItemBase::OnBeginOverlap);
	itemMesh->OnComponentEndOverlap.AddDynamic(this, &APickItemBase::OnEndOverlap);
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
		mainPlayer->AddHungry(25.0f);

		itemMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		Destroy();
	}
}

void APickItemBase::OnEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
                                 UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
}
