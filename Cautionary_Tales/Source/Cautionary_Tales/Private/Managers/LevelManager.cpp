// Fill out your copyright notice in the Description page of Project Settings.


#include "Managers/LevelManager.h"
#include <Runtime/Engine/Classes/Kismet/GameplayStatics.h>
#include "Managers/SaveManager.h"
#include "GameWorld/SaveData/SaveData.h"


//TODO: Load level and character position via Save system
void ULevelManager::LoadLevel(const bool& IsNewGame)
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
