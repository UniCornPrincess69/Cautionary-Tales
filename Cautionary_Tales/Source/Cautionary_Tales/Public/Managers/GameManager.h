// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "GameManager.generated.h"

/**
 * 
 */
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnPlayerReady, APlayerCharacter*, Player);

class APlayerCharacter;
class AInGameUI;
UCLASS()
class CAUTIONARY_TALES_API UGameManager : public UGameInstanceSubsystem
{
	GENERATED_BODY()

		static auto GetGameInstance(const UObject& target) -> UGameInstance* const;

public:
	static auto Instantiate(const UObject& target) -> UGameManager* const;

	void SetPlayer(APlayerCharacter* player);
	FORCEINLINE void SetInGameUI(AInGameUI* UI) { InGameUI = UI; }

	FORCEINLINE AInGameUI* GetInGameUI(void) { return InGameUI; }
	FORCEINLINE APlayerCharacter* GetPlayer(void) { return Player; }
	class UUIManager* GetUIManager(void);

	UPROPERTY(BlueprintAssignable)
	FOnPlayerReady OnPlayerReady;

private:
	virtual void Initialize(FSubsystemCollectionBase& collection) override;
	virtual void Deinitialize() override;

	APlayerCharacter* Player = nullptr;
	AInGameUI* InGameUI = nullptr;
};
