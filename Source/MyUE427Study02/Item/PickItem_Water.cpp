// Fill out your copyright notice in the Description page of Project Settings.


#include "PickItem_Water.h"

#include "MyUE427Study02/Player/MainPlayer.h"

APickItem_Water::APickItem_Water()
{
	waterValue = 25.0f;
}

void APickItem_Water::DoBeginOverlap(AMainPlayer* mainPlayer)
{
	mainPlayer->AddSaturation(waterValue);
}
