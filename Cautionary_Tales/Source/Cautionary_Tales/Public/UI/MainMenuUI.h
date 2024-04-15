// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "MainMenuUI.generated.h"

/**
 * 
 */
UCLASS()
class CAUTIONARY_TALES_API AMainMenuUI : public AHUD
{
	GENERATED_BODY()

		AMainMenuUI();

private:
	void SetMainMenu(void);

	class UUserWidget* MainMenuWidget = nullptr;

	const FString WidgetPath = FString(TEXT("/Game/Assets/Blueprints/UI/BP_MainMenuUI"));
	
};
