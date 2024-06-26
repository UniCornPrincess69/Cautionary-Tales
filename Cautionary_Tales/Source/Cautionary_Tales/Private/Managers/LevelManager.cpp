// Fill out your copyright notice in the Description page of Project Settings.


#include "Managers/LevelManager.h"
#include <Runtime/Engine/Classes/Kismet/GameplayStatics.h>
#include "Managers/SaveManager.h"
#include "GameWorld/SaveData/SaveData.h"
#include "Managers/GameManager.h"
#include "Player/TestCharacter.h"
#include "GameWorld/LevelScriptActors/BaseLevelScriptActor.h"

//TODO: Look at level streaming
//TODO: Load level and character position via Save system
void ULevelManager::LoadGame(const bool& IsNewGame)
{
	auto world = GetWorld();

	if (world)
	{
		if (IsNewGame)
		{
			UGameplayStatics::OpenLevel(world, *Levels.Find(ONE));
		}
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
	PlayerCharacter->OnTriggerOverlap.AddUniqueDynamic(this, &ULevelManager::LoadLevel);
}

void ULevelManager::DelayUnload()
{
	UGameplayStatics::UnloadStreamLevel(GetWorld(), "Level_01", FLatentActionInfo(), true);
}

void ULevelManager::Initialize(FSubsystemCollectionBase& collection)
{
	Super::Initialize(collection);
}

void ULevelManager::Deinitialize()
{
	if (PlayerCharacter) PlayerCharacter->OnTriggerOverlap.RemoveDynamic(this, &ULevelManager::LoadLevel);
	GetWorld()->GetTimerManager().ClearTimer(Handle);
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
			UGameplayStatics::LoadStreamLevel(world, "Level_02", true, true, FLatentActionInfo());
			world->GetTimerManager().SetTimer(Handle, FTimerDelegate::CreateUObject(this, &ULevelManager::DelayUnload), 1.f, false);
			GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Orange, TEXT("TEST"));
			
		}

	}
}


