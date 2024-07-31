// Fill out your copyright notice in the Description page of Project Settings.


#include "Managers/AudioManager.h"
#include "Sound/AmbientSound.h"
#include "Managers/GameManager.h"

void UAudioManager::StopCurrentAmbient(void)
{
	CurrentAmbient->Stop();
	CurrentAmbient->Destroy();
}

void UAudioManager::Initialize(FSubsystemCollectionBase& collection)
{
	Super::Initialize(collection);
	Manager = UGameManager::Instantiate(*this);
	if (Manager) Manager->SetAudioManager(this);

	
}

void UAudioManager::Deinitialize()
{
}
