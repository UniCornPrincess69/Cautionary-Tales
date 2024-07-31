// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "GameManager.generated.h"

/**
 * 
 */
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnPlayerReady, ATestCharacter*, Player);

class AStruwwel;
class APlayerCharacter;
class AInGameUI;
class ATestCharacter;
class AStruwwelController;
class ULevelManager;
class USaveManager;
class UAudioManager;
UCLASS()
class CAUTIONARY_TALES_API UGameManager : public UGameInstanceSubsystem
{
	GENERATED_BODY()

		static auto GetGameInstance(const UObject& target) -> UGameInstance* const;

public:
	static auto Instantiate(const UObject& target) -> UGameManager* const;

	void SetPlayer(ATestCharacter* player);
	void SetEnemy(AStruwwel* struwwel);
	inline void SetInGameUI(AInGameUI* UI) { InGameUI = UI; }
	inline void SetLevelManager(ULevelManager* levelManager) { LevelManager = levelManager; }
	inline void SetNewGameBool(bool isNewGame) { IsNewGame = isNewGame; }
	inline void SetSaveManager(USaveManager* saveManager) { SaveManager = saveManager; }
	inline void SetEnemyActive(bool isEnemyActive) { IsEnemyActive = isEnemyActive; }
	inline void SetAudioManager(UAudioManager* audio) { AudioManager = audio; }

	inline AInGameUI* GetInGameUI(void) { return InGameUI; }
	inline ATestCharacter* GetPlayer(void) { return Player; }
	inline AStruwwel* GetEnemy(void) { return Struwwel; }
	inline ULevelManager* GetLevelManager(void) { return LevelManager; }
	inline bool GetNewGameBool(void) { return IsNewGame; }
	inline USaveManager* GetSaveManager(void) { return SaveManager; }
	class UUIManager* GetUIManager(void);
	inline bool GetEnemyActive(void) { return IsEnemyActive; }
	inline UAudioManager* GetAudioManager(void) { return AudioManager; }

	UPROPERTY(BlueprintAssignable)
	FOnPlayerReady OnPlayerReady;


private:
	virtual void Initialize(FSubsystemCollectionBase& collection) override;
	virtual void Deinitialize() override;

	void DelayedPlayerReadyCallback(void);

	FTimerHandle TimerHandle;

	ATestCharacter* Player = nullptr;
	AStruwwel* Struwwel = nullptr;
	AInGameUI* InGameUI = nullptr;
	AStruwwelController* AIController = nullptr;
	ULevelManager* LevelManager = nullptr;
	USaveManager* SaveManager = nullptr;
	UAudioManager* AudioManager = nullptr;

	bool IsNewGame = false;
	bool IsEnemyActive = false;
};
