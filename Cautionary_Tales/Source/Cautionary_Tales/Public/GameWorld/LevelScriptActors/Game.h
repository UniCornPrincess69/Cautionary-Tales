// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/LevelScriptActor.h"
#include "Game.generated.h"

/**
 * 
 */
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnLevelLoaded);

UCLASS()
class CAUTIONARY_TALES_API AGame : public ALevelScriptActor
{
	GENERATED_BODY()

public:
	FOnLevelLoaded OnLevelLoaded;
	
};
