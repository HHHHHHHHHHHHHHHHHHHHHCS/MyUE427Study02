// Fill out your copyright notice in the Description page of Project Settings.


#include "PickItem_Food.h"

#include "MyUE427Study02/Player/MainPlayer.h"

APickItem_Food::APickItem_Food()
{
	foodValue = 25.0f;
}

void APickItem_Food::DoBeginOverlap(AMainPlayer* mainPlayer)
{
	mainPlayer->AddHungry(foodValue);
}
