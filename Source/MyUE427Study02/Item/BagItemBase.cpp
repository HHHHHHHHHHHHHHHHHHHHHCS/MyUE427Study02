// Fill out your copyright notice in the Description page of Project Settings.


#include "BagItemBase.h"

// Sets default values
ABagItemBase::ABagItemBase()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	displayMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ItemDisplayMesh"));
	SetRootComponent(displayMesh);

	itemStateData.data.DataTable
		= LoadObject<UDataTable>(nullptr, TEXT("DataTable'/Game/Blueprints/Data/BagItemDataTable.BagItemDataTable'"));
	itemStateData.data.RowName = "Empty";

	
	const UDataTable* table = itemStateData.data.DataTable;

	if (table != nullptr)
	{
		itemData = table->FindRow<FBagItemData>(itemStateData.data.RowName, "");

		if (itemData != nullptr && itemData->itemMesh != nullptr)
		{
			displayMesh->SetStaticMesh(itemData->itemMesh);
		}
	}
}

// Called when the game starts or when spawned
void ABagItemBase::BeginPlay()
{
	Super::BeginPlay();


	//构造函数的时候无法识别，  需要在beginplay中重新设置
	//如果物体没有碰撞资源， 就不会产生碰撞
	const UDataTable* table = itemStateData.data.DataTable;

	if (table != nullptr)
	{
		itemData = table->FindRow<FBagItemData>(itemStateData.data.RowName, "");

		if (itemData != nullptr && itemData->itemMesh != nullptr)
		{
			displayMesh->SetStaticMesh(itemData->itemMesh);
		}
	}
}

// Called every frame
void ABagItemBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
