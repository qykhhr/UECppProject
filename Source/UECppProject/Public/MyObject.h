// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
//#include "Engine/Classes/Engine/DataTale.h"
#include <Engine/Classes/Engine/DataTable.h>
#include "MyObject.generated.h"

USTRUCT(BlueprintType)
struct FMyDataTableStruct : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MyTestDataTableStruct")
		float Health;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MyTestDataTableStruct")
		FString Name;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MyTestDataTableStruct")
		int32 level;

};
/**
 * 
 */
UCLASS()
class UECPPPROJECT_API UMyObject : public UObject
{
	GENERATED_BODY()
	
};
