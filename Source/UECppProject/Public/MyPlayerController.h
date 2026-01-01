// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "MyPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class UECPPPROJECT_API AMyPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	virtual void SetupInputComponent() override;

	//鼠标滚轮向上滚  绑定的事件
	void WheelUpFunction();
	//鼠标滚轮向下滚  绑定的事件
	void WheelDownFunction();

	virtual void BeginPlay() override;
};
