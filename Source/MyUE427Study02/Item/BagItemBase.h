// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Data/ItemStateData.h"
#include "GameFramework/Actor.h"
#include "BagItemBase.generated.h"

UCLASS()
class MYUE427STUDY02_API ABagItemBase : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ABagItemBase();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Item")
	UStaticMeshComponent* displayMesh;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Item")
	FItemStateData itemStateData;

	// 加上UPROPERTY会编译失败
	// UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Item")
	FBagItemData* itemData;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
