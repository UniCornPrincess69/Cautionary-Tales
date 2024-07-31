// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameWorld/LevelScriptActors/BaseLevelScriptActor.h"
#include "LevelScriptActor_Level_02.generated.h"

/**
 * 
 */
UCLASS()
class CAUTIONARY_TALES_API ALevelScriptActor_Level_02 : public ABaseLevelScriptActor
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type endPlayReason) override;

private:
	class ULevelManager* LevelManager = nullptr;
	class ATeleporterZone* TPZone = nullptr;
	class AGame* Game = nullptr;
	class UGameManager* GM = nullptr;
};
