// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/Button.h"
#include "Blueprint/UserWidget.h"
#include "MyUserWidget.generated.h"

/**
 * 
 */
UCLASS()
class UECPPPROJECT_API UMyUserWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(meta = (BindWidget))
		UButton* ButtonStart;
	UPROPERTY(meta = (BindWidget))
		UButton* ButtonQuit;

	virtual bool Initialize() override;

	UFUNCTION()
		void Start();
	UFUNCTION()
		void Quit();
};
