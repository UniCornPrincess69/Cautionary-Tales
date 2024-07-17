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


	//inline void SetCurrentLevel(FName currentLevel) { CurrentLevel = currentLevel; }
	void PlayerReady(ATestCharacter* player);
private:
	void Instantiate();
	UFUNCTION()
	void DelayUnload(FName currentLevel);

	virtual void Initialize(FSubsystemCollectionBase& collection) override;
	virtual void Deinitialize() override;

	UFUNCTION()
	void LoadLevel();



	FTimerHandle Handle;

	const int32 ONE = 1;
	const FName FIRSTLEVEL = FName(TEXT("PersistentLevel"));

	FString CurrentLevel = FString("");


	UGameManager* GM = nullptr;
	ATestCharacter* PlayerCharacter = nullptr;
};
