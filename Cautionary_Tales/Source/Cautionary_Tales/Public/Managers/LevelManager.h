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
	void LoadLevel(const FName& LevelName);
};
