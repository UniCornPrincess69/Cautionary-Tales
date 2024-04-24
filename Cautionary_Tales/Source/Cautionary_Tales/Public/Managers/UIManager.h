// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/WorldSubsystem.h"
#include "UIManager.generated.h"

/**
 * 
 */
UCLASS()
class CAUTIONARY_TALES_API UUIManager : public UWorldSubsystem
{
	GENERATED_BODY()

public:
	void StartGame(const UObject* target);
	void QuitGame(const UObject* target);
	void PauseGame(const UObject* target, bool isPaused);
	void DeathScreen(const UObject* target);
	void ToMainMenu(const UObject* target);

private:
	const FName MAIN_MENU = FName(TEXT("MainMenu")); 
	const FName LEVEL_ONE = FName(TEXT("Level_01")); 
	const FName LEVEL_TWO = FName(TEXT("Level_02"));
	const FName LEVEL_THREE = FName(TEXT("Level_03"));
	
};
