// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "InGameUI.generated.h"

/**
 * 
 */
class UUserWidget;
UCLASS()
class CAUTIONARY_TALES_API AInGameUI : public AHUD
{
	GENERATED_BODY()
		AInGameUI();

public:
	void InitWidgets(void);
	void SetPauseWidget(void);
	void SetEndWidget(void);

	UFUNCTION()
	void SetDeathScreen();

	UFUNCTION()
	void SetupCallback(class ATestCharacter* character);

protected:
	virtual void EndPlay(const EEndPlayReason::Type endPlayReason) override;

private:
	APlayerController* Player = nullptr;
	class UGameManager* GM = nullptr;
	class ATestCharacter* Character = nullptr;
	UUserWidget* PauseWidget = nullptr;
	UUserWidget* EndWidget = nullptr;
	UUserWidget* DeathWidget = nullptr;

	FInputModeGameOnly Game;
	FInputModeGameAndUI Both;

#pragma region Constants
	const FString PauseHUDPath = FString(TEXT("/Game/Assets/Blueprints/UI/BP_PauseMenuUI"));
	const FString EndHUDPath = FString(TEXT("/Game/Assets/Blueprints/UI/BP_EndScreen"));
	const FString DeathHUDPath = FString(TEXT("/Game/Assets/Blueprints/UI/BP_DeathScreenUI"));
#pragma endregion
	
};
