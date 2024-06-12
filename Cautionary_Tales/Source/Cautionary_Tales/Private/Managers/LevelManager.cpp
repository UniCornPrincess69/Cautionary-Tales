// Fill out your copyright notice in the Description page of Project Settings.


#include "Managers/LevelManager.h"
#include <Runtime/Engine/Classes/Kismet/GameplayStatics.h>
#include "Managers/SaveManager.h"
#include "GameWorld/SaveData/SaveData.h"
#include "Managers/GameManager.h"
#include "Player/PlayerCharacter.h"
#include "Player/TestCharacter.h"


//TODO: Load level and character position via Save system
void ULevelManager::LoadGame(const bool& IsNewGame)
{
	auto world = GetWorld();

	if (world)
	{
		if (IsNewGame) UGameplayStatics::OpenLevel(world, *Levels.Find(ONE));
		else
		{
			auto data = world->GetSubsystem<USaveManager>()->LoadGame();
			UGameplayStatics::OpenLevel(world, data->LevelName);
		}
	}
}

void ULevelManager::SetGameManager(UGameManager* GameManager)
{
	GM = GameManager;
	PlayerCharacter = GM->GetPlayer();

	PlayerCharacter->OnTriggerOverlap.AddDynamic(this, &ULevelManager::LoadLevel);
}

void ULevelManager::Initialize(FSubsystemCollectionBase& collection)
{
	Super::Initialize(collection);
}

void ULevelManager::Deinitialize()
{
	if (PlayerCharacter)
	{
		PlayerCharacter->OnTriggerOverlap.RemoveDynamic(this, &ULevelManager::LoadLevel);
	}
}


void ULevelManager::LoadLevel(void)
{
	auto world = GetWorld();

	if (world)
	{
		auto level = UGameplayStatics::GetCurrentLevelName(world);
		const int32* levelNumber = nullptr;

		for (const auto& pair : Levels)
		{
			if (pair.Value == FName(level))
			{
				levelNumber = &pair.Key;
				break;
			}
		}


		if (levelNumber)
		{
			auto nextLevel = *levelNumber + ONE;
			UE_LOG(LogTemp, Warning, TEXT("%d"), nextLevel);
			UGameplayStatics::OpenLevel(world, *Levels.Find(nextLevel));
		}

	}
}


