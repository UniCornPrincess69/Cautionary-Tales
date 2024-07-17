// Fill out your copyright notice in the Description page of Project Settings.


#include "Managers/LevelManager.h"
#include <Runtime/Engine/Classes/Kismet/GameplayStatics.h>
#include "Managers/SaveManager.h"
#include "GameWorld/SaveData/SaveData.h"
#include "Managers/GameManager.h"
#include "Player/TestCharacter.h"
#include "GameWorld/LevelScriptActors/BaseLevelScriptActor.h"

void ULevelManager::LoadGame(const bool& IsNewGame)
{
	auto world = GetWorld();
	if(world) Instantiate();
	if (GM) GM->SetNewGameBool(IsNewGame);
	if (world)
	{
		UGameplayStatics::OpenLevel(world, FIRSTLEVEL);
		/*if(!IsNewGame)
		{
			auto data = world->GetSubsystem<USaveManager>()->LoadGame();
			UGameplayStatics::LoadStreamLevel(world, FName(data->StreamingLevelName), true, true, FLatentActionInfo());
		}*/
	}
}


void ULevelManager::Instantiate()
{
	GM = UGameManager::Instantiate(*this);
}

void ULevelManager::DelayUnload(FName currentLevel)
{
	UGameplayStatics::UnloadStreamLevel(GetWorld(), currentLevel, FLatentActionInfo(), true);
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

	}
}

void ULevelManager::PlayerReady(ATestCharacter* player)
{
	PlayerCharacter = player;
	PlayerCharacter->OnTriggerOverlap.AddUniqueDynamic(this, &ULevelManager::LoadLevel);
}




