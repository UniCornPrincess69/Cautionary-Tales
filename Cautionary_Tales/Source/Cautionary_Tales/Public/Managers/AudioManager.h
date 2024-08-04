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

	inline void SetMastervolume(float volume) { MasterVolume = volume; }
	inline void SetSFXvolume(float volume) { SFXVolume = volume; }
	inline void SetMusicvolume(float volume) { MusicVolume = volume; }
	void SaveVolume(void);

	void StopCurrentAmbient(void);

private:
	virtual void Initialize(FSubsystemCollectionBase& collection) override;
	virtual void Deinitialize(void) override;

	class UGameManager* Manager = nullptr;
	class USaveManager* Save = nullptr;
	AAmbientSound* CurrentAmbient = nullptr;
	struct FVolumeData* VolumeData = nullptr;

	FTimerHandle Handle;

	float MasterVolume = 1.f;
	float SFXVolume = 1.f;
	float MusicVolume = 1.f;
	
};
