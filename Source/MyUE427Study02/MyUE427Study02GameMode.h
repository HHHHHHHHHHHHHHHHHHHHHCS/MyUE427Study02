// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "MyUE427Study02GameMode.generated.h"

UCLASS(minimalapi)
class AMyUE427Study02GameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="UI Widgets")
	TSubclassOf<class UUserWidget> mainUIClass;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="UI Widgets")
	UUserWidget* mainUI;

public:
	AMyUE427Study02GameMode();

protected:
	virtual void BeginPlay() override;
};
