// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SphereComponent.h"
#include "GameFramework/Actor.h"
#include "MyUE427Study02/Player/MainPlayer.h"
#include "PickItemBase.generated.h"

UCLASS()
class MYUE427STUDY02_API APickItemBase : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	APickItemBase();

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Item")
	USphereComponent* itemCollision;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Item")
	UStaticMeshComponent* itemMesh;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	virtual void OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	                            UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
	                            const FHitResult& SweepResult);

	virtual void DoBeginOverlap(AMainPlayer* mainPlayer);

	UFUNCTION()
	virtual void OnEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	                          UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	virtual void DoEndOverlap(AMainPlayer* mainPlayer);
};
