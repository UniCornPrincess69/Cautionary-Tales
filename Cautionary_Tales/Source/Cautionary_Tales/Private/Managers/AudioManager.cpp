// Fill out your copyright notice in the Description page of Project Settings.


#include "Managers/AudioManager.h"
#include "Sound/AmbientSound.h"
#include "Managers/GameManager.h"
#include "Managers/SaveManager.h"
#include "GameWorld/SaveData/VolumeData.h"

void UAudioManager::StopCurrentAmbient(void)
{
	CurrentAmbient->Stop();
	CurrentAmbient->Destroy();
}

void UAudioManager::Initialize(FSubsystemCollectionBase& collection)
{
	Super::Initialize(collection);
	Manager = UGameManager::Instantiate(*this);
	if (Manager)
	{
		Manager->SetAudioManager(this);
		Save = Manager->GetSaveManager();
		//TODO: Delegate for the save manager and subsequent loading of the volumes
		if (!Save) GetWorld()->GetTimerManager().SetTimer(Handle, [this]() {Save = Manager->GetSaveManager(); }, 3.f, false);
		if (Save) VolumeData = Save->LoadVolume();
	}
	
}

void UAudioManager::Deinitialize()
{
	Super::Deinitialize();
	GetWorld()->GetTimerManager().ClearTimer(Handle);
}

void UAudioManager::SaveVolume(void)
{
	if (!Save) Manager->GetSaveManager();
	if (Save) Save->SaveVolumes(MasterVolume, SFXVolume, MusicVolume);
}
