// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/LevelScriptActor.h"
#include "Game.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnLevelLoaded);

class ATestCharacter;
class ATeleporterZone;
UCLASS()
class CAUTIONARY_TALES_API AGame : public ALevelScriptActor
{
	GENERATED_BODY()

public:
	FOnLevelLoaded OnLevelLoaded;

	void UpdateTeleporter(ATeleporterZone* newZone);

protected:
	virtual void BeginPlay() override;

	virtual void EndPlay(const EEndPlayReason::Type endPlayReason) override;

private:
	UFUNCTION()
	void TeleportPlayer();

	UFUNCTION()
	void PlayerReady(ATestCharacter* player);

	ATeleporterZone* TeleportZone = nullptr;
	class UGameManager* Manager = nullptr;
	class ATestCharacter* Player = nullptr;
	
};
