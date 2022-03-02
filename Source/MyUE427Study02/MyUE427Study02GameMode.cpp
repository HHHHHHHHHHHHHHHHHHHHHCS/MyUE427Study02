// Copyright Epic Games, Inc. All Rights Reserved.

#include "MyUE427Study02GameMode.h"
#include "Player/MainPlayer.h"
#include "UObject/ConstructorHelpers.h"

AMyUE427Study02GameMode::AMyUE427Study02GameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/Blueprints/MainPlayer"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
