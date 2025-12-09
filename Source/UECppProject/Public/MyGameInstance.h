// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "MyGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class UECPPPROJECT_API UMyGameInstance : public UGameInstance
{
	GENERATED_BODY()
	
public:
	UMyGameInstance();
	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "MyInstance")
		FString MyAppID;
	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "MyInstance")
		FString MyUserID;
	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "MyInstance")
		FString MyName;

};
