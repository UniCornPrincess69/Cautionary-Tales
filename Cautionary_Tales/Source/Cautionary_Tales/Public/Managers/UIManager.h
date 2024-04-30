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
	void StartGame(const UObject* Target);
	void ContinueGame(const UObject* Target);
	void QuitGame(const UObject* Target);
	void QuitAndSave(const UObject* Target);
	void PauseGame(const UObject* Target, bool IsPaused);
	void DeathScreen(const UObject* Target);
	void ToMainMenu(const UObject* Target);

private:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;

	const FName SAVE = FName(TEXT("Save"));
	const FName MAIN_MENU = FName(TEXT("MainMenu")); 
	const FName LEVEL_ONE = FName(TEXT("Level_01")); 
	const FName LEVEL_TWO = FName(TEXT("Level_02"));
	const FName LEVEL_THREE = FName(TEXT("Level_03"));
	
};
