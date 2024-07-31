// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/WorldSubsystem.h"
#include "AudioManager.generated.h"

/**
 * 
 */
class AAmbientSound;
UCLASS()
class CAUTIONARY_TALES_API UAudioManager : public UWorldSubsystem
{
	GENERATED_BODY()
	
public:
	inline void SetCurrentAmbient(AAmbientSound* sound) { CurrentAmbient = sound; }

	void StopCurrentAmbient(void);

private:
	virtual void Initialize(FSubsystemCollectionBase& collection) override;
	virtual void Deinitialize() override;

	class UGameManager* Manager = nullptr;
	AAmbientSound* CurrentAmbient = nullptr;
	
};
