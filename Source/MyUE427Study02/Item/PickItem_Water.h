// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PickItemBase.h"
#include "PickItem_Water.generated.h"

/**
 * 
 */
UCLASS()
class MYUE427STUDY02_API APickItem_Water : public APickItemBase
{
	GENERATED_BODY()

public:
	APickItem_Water();
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Item")
	float waterValue;

public:
	virtual void DoBeginOverlap(AMainPlayer* mainPlayer) override;
};
