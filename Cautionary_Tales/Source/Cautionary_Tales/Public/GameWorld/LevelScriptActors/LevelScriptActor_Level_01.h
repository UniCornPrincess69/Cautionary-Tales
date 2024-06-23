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

protected:
	virtual void BeginPlay() override;
	
};
