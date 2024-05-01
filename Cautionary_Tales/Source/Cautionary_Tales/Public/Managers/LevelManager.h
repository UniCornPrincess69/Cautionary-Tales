// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/WorldSubsystem.h"
#include "LevelManager.generated.h"

/**
 * 
 */

UCLASS()
class CAUTIONARY_TALES_API ULevelManager : public UWorldSubsystem
{
	GENERATED_BODY()
	
public:
	void LoadLevel(const bool& IsNewGame);

private:
	TMap<int32, FName> Levels = 
	{
		{0, FName("MainMenu")},
		{1, FName("Level_01")},
		{2, FName("Level_02")},
		{3, FName("Level_03")}
	};
	const int32 ONE = 1;
};
