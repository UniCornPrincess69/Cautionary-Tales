// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/LevelScriptActor.h"
#include "Game.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnLevelLoaded);

class ATestCharacter;
class ATeleporterZone;
class APuzzleTrigger;
class AProgressSpotLight;
class AInteractableBox;
class AProgressionTrigger;
class APuzzleSpotLight;
UCLASS()
class CAUTIONARY_TALES_API AGame : public ALevelScriptActor
{
	GENERATED_BODY()

public:
	FOnLevelLoaded OnLevelLoaded;

	void UpdateTeleporter(ATeleporterZone* newZone);

	inline void SetProgressionTrigger(AProgressionTrigger* trigger) { ProgressTrigger = trigger; }
	inline void SetProgressSpotLight(AProgressSpotLight* spotLight) { ProgressSpotLight = spotLight; }
	inline void SetPuzzleSpotLight(APuzzleSpotLight* spotLight) { PuzzleSpotLight = spotLight; }
	inline void SetPuzzleTrigger(APuzzleTrigger* trigger) { PuzzleTrigger = trigger; }
	inline void SetInteractableBox(AInteractableBox* box) { InteractableBox = box; }
	
	inline AProgressionTrigger* GetProgressionTrigger(void) { return ProgressTrigger; }
	inline AProgressSpotLight* GetProgressSpotLight(void) { return ProgressSpotLight; }
	inline APuzzleSpotLight* GetPuzzleSpotLight(void) { return PuzzleSpotLight; }
	inline APuzzleTrigger* GetPuzzleTrigger(void) { return PuzzleTrigger; }
	inline AInteractableBox* GetInteractableBox(void) { return InteractableBox; }

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
	class USaveManager* SaveManager = nullptr;

	APuzzleTrigger* PuzzleTrigger = nullptr;
	AProgressSpotLight* ProgressSpotLight = nullptr;
	AInteractableBox* InteractableBox = nullptr;
	AProgressionTrigger* ProgressTrigger = nullptr;
	APuzzleSpotLight* PuzzleSpotLight = nullptr;

	const FName FIRSTLEVEL = FName(TEXT("Level_01"));
};
