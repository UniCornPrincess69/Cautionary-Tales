// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/WorldSubsystem.h"
#include "AudioManager.generated.h"

/**
 * 
 */
UCLASS()
class CAUTIONARY_TALES_API UAudioManager : public UWorldSubsystem
{
	GENERATED_BODY()
	

private:
	virtual void Initialize(FSubsystemCollectionBase& collection) override;
	virtual void Deinitialize() override;
};
