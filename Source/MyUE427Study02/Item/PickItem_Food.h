// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PickItemBase.h"
#include "PickItem_Food.generated.h"

/**
 * 
 */
UCLASS()
class MYUE427STUDY02_API APickItem_Food : public APickItemBase
{
	GENERATED_BODY()
	
public:
	APickItem_Food();
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Item")
	float foodValue;

public:
	virtual void DoBeginOverlap(AMainPlayer* mainPlayer) override;
};
