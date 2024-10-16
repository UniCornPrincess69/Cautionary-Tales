// Fill out your copyright notice in the Description page of Project Settings.


#include "Managers/AudioManager.h"
#include "Sound/AmbientSound.h"
#include "Managers/GameManager.h"
#include "Managers/SaveManager.h"
#include "GameWorld/SaveData/VolumeData.h"

void UAudioManager::StopCurrentAmbient(void)
{
	if (CurrentAmbient)
	{
		CurrentAmbient->Stop();
		CurrentAmbient->Destroy();

	}
}

void UAudioManager::Initialize(FSubsystemCollectionBase& collection)
{
	Super::Initialize(collection);
	Manager = UGameManager::Instantiate(*this);
	if (Manager)
	{
		Manager->SetAudioManager(this);
		Manager->OnSaveManagerInit.AddUniqueDynamic(this, &UAudioManager::SaveManagerCallback);
	}
}

void UAudioManager::Deinitialize()
{
	Super::Deinitialize();
	if (Manager) Manager->OnSaveManagerInit.RemoveDynamic(this, &UAudioManager::SaveManagerCallback);
}

void UAudioManager::SaveManagerCallback()
{
	Save = Manager->GetSaveManager();
	VolumeData = Save->LoadVolume();
}

void UAudioManager::SaveVolume(void)
{
	if (Save) Save->SaveVolumes(MasterVolume, SFXVolume, MusicVolume);
}

void UAudioManager::GetAudioValues(float& masterVolumeOUT, float& musicVolumeOUT, float& sfxVolumeOUT)
{
	if (!VolumeData)
	{
		VolumeData = Save->LoadVolume();
		if (!VolumeData)
		{
			masterVolumeOUT = 1.f;
			musicVolumeOUT = 1.f;
			sfxVolumeOUT = 1.f;
		}
	}

	if (VolumeData)
	{
		masterVolumeOUT = VolumeData->MasterVolume;
		musicVolumeOUT = VolumeData->MusicVolume;
		sfxVolumeOUT = VolumeData->SFXVolume;
	}
}
