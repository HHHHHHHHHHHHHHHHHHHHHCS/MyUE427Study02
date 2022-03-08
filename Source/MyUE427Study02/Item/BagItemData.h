// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SphereComponent.h"
#include "Engine/DataTable.h"
#include "BagItemData.generated.h"

USTRUCT(BlueprintType)
struct FBagItemData : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Item")
	FString name;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Item")
	FString desc;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Item")
	UTexture2D* image;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Item")
	UStaticMesh* itemMesh;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Item")
	bool canStack;
};
