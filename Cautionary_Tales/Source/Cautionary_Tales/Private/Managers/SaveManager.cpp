// Fill out your copyright notice in the Description page of Project Settings.


#include "Managers/SaveManager.h"
#include "GameWorld/SaveData/SaveData.h"
#include "Managers/GameManager.h"
#include <Runtime/Engine/Classes/Kismet/GameplayStatics.h>
#include "Player/PlayerCharacter.h"


FSaveData USaveManager::CreateSaveData(void)
{
	FSaveData data;

	auto GM = UGameManager::Instantiate(*this);
	auto world = GetWorld();

	if (GM && world)
	{
		data.PlayerPosition = GM->GetPlayer()->GetActorLocation();
		data.LevelName = StaticCast<FName>(UGameplayStatics::GetCurrentLevelName(world));
	}
	
	return data;
}

void USaveManager::SaveGame(const FName& SaveName)
{
	if (DataTable)
	{
		if (!CheckSave(DataTable, SaveName)) DataTable->AddRow(SaveName, CreateSaveData());
		else
		{
			DataTable->RemoveRow(SaveName);
			DataTable->AddRow(SaveName, CreateSaveData());
		}
	}
}

FSaveData* USaveManager::LoadGame(const FName& SaveName)
{
	FSaveData* saveData;
	
	if (CheckSave(DataTable, SaveName))
	{
		return nullptr;
	}
	else
	{
		saveData = DataTable->FindRow<FSaveData>(SaveName, TEXT(""));
	}
	
	return saveData;
}


void USaveManager::Initialize(FSubsystemCollectionBase& collection)
{
	Super::Initialize(collection);
	DataTable = LoadObject<UDataTable>(nullptr, (TCHAR*)(*SaveDataPath));
}

void USaveManager::Deinitialize()
{
	Super::Deinitialize();
}

bool USaveManager::CheckSave(const UDataTable* Data, const FName& SaveName)
{
	return Data->FindRow<FSaveData>(SaveName, TEXT("")) ? true : false;
}
