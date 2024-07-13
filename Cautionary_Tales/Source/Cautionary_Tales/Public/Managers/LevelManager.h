// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/WorldSubsystem.h"
#include "LevelManager.generated.h"

/**
 * 
 */
class ATestCharacter;
class UGameManager;
class ABaseLevelScriptActor;
UCLASS()
class CAUTIONARY_TALES_API ULevelManager : public UWorldSubsystem
{
	GENERATED_BODY()

public:
	void LoadGame(const bool& IsNewGame);

	inline void SetLevelOne(ABaseLevelScriptActor* levelOne) { LevelOne = levelOne; }
	inline void SetLevelTwo(ABaseLevelScriptActor* levelTwo) { LevelTwo = levelTwo; }

	void Instantiate(UGameManager* manager);
	//inline void SetCurrentLevel(FName currentLevel) { CurrentLevel = currentLevel; }
private:
	UFUNCTION()
	void DelayUnload(FName currentLevel);

	virtual void Initialize(FSubsystemCollectionBase& collection) override;
	virtual void Deinitialize() override;

	UFUNCTION()
	void LoadLevel();


	FTimerHandle Handle;

	TMap<int32, FName> Levels = 
	{
		{0, FName("MainMenu")},
		{1, FName("PersistentLevel")},
		{2, FName("Level_01")},
		{3, FName("Level_02")},
		{4, FName("Level_03")},
		{5, FName("End")}
	};
	const int32 ONE = 1;

	FString CurrentLevel = FString("");

	ABaseLevelScriptActor* LevelOne = nullptr;
	ABaseLevelScriptActor* LevelTwo = nullptr;

	UGameManager* GM = nullptr;
	ATestCharacter* PlayerCharacter = nullptr;
};
