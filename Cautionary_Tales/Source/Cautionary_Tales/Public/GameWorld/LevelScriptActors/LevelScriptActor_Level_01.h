// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameWorld/LevelScriptActors/BaseLevelScriptActor.h"
#include "LevelScriptActor_Level_01.generated.h"

/**
 * 
 */
UCLASS()
class CAUTIONARY_TALES_API ALevelScriptActor_Level_01 : public ABaseLevelScriptActor
{
	GENERATED_BODY()

	ALevelScriptActor_Level_01();

protected:
	virtual void BeginPlay() override;

	virtual void EndPlay(const EEndPlayReason::Type endPlayReason) override;
	
private:
	class ULevelManager* LevelManager = nullptr;
	FName LevelName = FName(TEXT("Level_01"));
	class ATeleporterZone* TPZone = nullptr;
};
