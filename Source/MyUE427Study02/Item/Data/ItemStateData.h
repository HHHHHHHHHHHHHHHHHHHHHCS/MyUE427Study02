#pragma once

#include "CoreMinimal.h"
#include "BagItemData.h"
#include "Engine/DataTable.h"
#include "ItemStateData.generated.h"

USTRUCT(BlueprintType)
struct FItemStateData : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Item")
	FDataTableRowHandle data;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Item")
	int amount;
};
