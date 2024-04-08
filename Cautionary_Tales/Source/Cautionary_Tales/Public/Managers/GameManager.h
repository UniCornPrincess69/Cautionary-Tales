// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "GameManager.generated.h"

/**
 * 
 */
class APlayerCharacter;
UCLASS()
class CAUTIONARY_TALES_API UGameManager : public UGameInstanceSubsystem
{
	GENERATED_BODY()

		static auto GetGameInstance(const UObject& target) -> UGameInstance* const;

public:
	static auto Instantiate(const UObject& target) -> UGameManager* const;

	FORCEINLINE void SetPlayer(APlayerCharacter* player) { Player = player; }
	FORCEINLINE APlayerCharacter* GetPlayer() { return Player; }

private:
	virtual void Initialize(FSubsystemCollectionBase& collection) override;
	virtual void Deinitialize() override;

	APlayerCharacter* Player = nullptr;
};
