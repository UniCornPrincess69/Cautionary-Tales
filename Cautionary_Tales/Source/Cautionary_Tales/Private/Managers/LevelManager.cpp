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
			auto levelOne = *Levels.Find(ONE);
			UGameplayStatics::OpenLevel(world, levelOne);
		}
		else
		{
			auto data = world->GetSubsystem<USaveManager>()->LoadGame();
			//TODO: Persistent Level needs to be always opened, streaming level needs adjustment
			UGameplayStatics::OpenLevel(world, data->LevelName);
		}
	}
}


void ULevelManager::Instantiate(UGameManager* manager)
{
	GM = manager;
	PlayerCharacter = GM->GetPlayer();
	PlayerCharacter->OnTriggerOverlap.AddUniqueDynamic(this, &ULevelManager::LoadLevel);
}

void ULevelManager::DelayUnload(FName currentLevel)
{
	UGameplayStatics::UnloadStreamLevel(GetWorld(), currentLevel, FLatentActionInfo(), true);
	UE_LOG(LogTemp, Warning, TEXT("Current level was %s"), currentLevel);
	GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Red, TEXT("Level unloaded"));
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
		const TArray<ULevelStreaming*>& streamingLevels = world->GetStreamingLevels();

		for (auto& streamingLevel : streamingLevels)
		{
			if (streamingLevel && streamingLevel->IsLevelLoaded())
			{
				CurrentLevel = streamingLevel->GetWorldAssetPackageName();
				auto idx = streamingLevels.IndexOfByKey(streamingLevel);
				auto nextLevelName = streamingLevels[idx + 1];
				UGameplayStatics::LoadStreamLevel(world, nextLevelName->GetWorldAssetPackageFName(), true, true, FLatentActionInfo());
				world->GetTimerManager().SetTimer(Handle, [&]() { this->DelayUnload(FName(CurrentLevel)); }, 1.f, false);
			}
		}





		/*auto level = UGameplayStatics::GetCurrentLevelName(world);
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
			UGameplayStatics::LoadStreamLevel(world, *Levels.Find(nextLevel), true, true, FLatentActionInfo());
			world->GetTimerManager().SetTimer(Handle, [&]() { this->DelayUnload(CurrentLevel); }, 1.f, false);
		}*/

	}
}




