// Copyright Epic Games, Inc. All Rights Reserved.

#include "MyUE427Study02GameMode.h"

#include "Blueprint/UserWidget.h"
#include "Kismet/GameplayStatics.h"
#include "Player/MainPlayer.h"
#include "UObject/ConstructorHelpers.h"

AMyUE427Study02GameMode::AMyUE427Study02GameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/Blueprints/Player/MainPlayer"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}

void AMyUE427Study02GameMode::BeginPlay()
{
	Super::BeginPlay();

	if (mainUIClass)
	{
		mainUI = CreateWidget<UUserWidget>(UGameplayStatics::GetPlayerController(this, 0), mainUIClass);
		if(mainUI)
		{
			mainUI->AddToViewport();
		}
	}
}
