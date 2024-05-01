// Fill out your copyright notice in the Description page of Project Settings.


#include "Managers/SaveManager.h"
#include "GameWorld/SaveData/SaveData.h"
#include "Managers/GameManager.h"
#include <Runtime/Engine/Classes/Kismet/GameplayStatics.h>
#include "Player/PlayerCharacter.h"
#include "JsonObjectConverter.h"
#include "Serialization/JsonSerializer.h"
#include "FileHelpers.h"



FSaveData USaveManager::CreateSaveData(void)
{
	FSaveData data;

	auto GM = UGameManager::Instantiate(*this);
	auto world = GetWorld();

	if (GM && world)
	{
		data.PlayerPosition = GM->GetPlayer()->GetActorLocation();
		data.LevelName = StaticCast<FName>(UGameplayStatics::GetCurrentLevelName(world));
		//TODO: Get Enemy location, probably some more info. Adjust SaveData accordingly
	}

	return data;
}

void USaveManager::SaveGame()
{
	if (DataTable)
	{
		auto saveData = CreateSaveData();

		if (!CheckSave(DataTable, SAVENAME)) DataTable->AddRow(SAVENAME, saveData);
		else
		{
			DataTable->RemoveRow(SAVENAME);
			DataTable->AddRow(SAVENAME, saveData);
			DataTable->Modify();
			DataTable->MarkPackageDirty();

			//TODO: SaveData check needs to be reworked. Only one file with given name should exist. 
			if (SaveData)
			{
				FString JsonString;
				FJsonObjectConverter::UStructToJsonObjectString(saveData, JsonString);

				FString FilePath = FPaths::ProjectSavedDir() + TEXT("SavedData.json");

				if (FFileHelper::SaveStringToFile(JsonString, *FilePath))
				{
					UE_LOG(LogTemp, Warning, TEXT("Success"));
				}
				else UE_LOG(LogTemp, Warning, TEXT("Failed"));
			}
		}
	}
}

FSaveData* USaveManager::LoadGame()
{
	if (!CheckSave(DataTable, SAVENAME))
	{
		return nullptr;
	}
	else
	{
		return SaveData;
	}
}


//TODO: Loading of saved file
void USaveManager::Initialize(FSubsystemCollectionBase& collection)
{
	Super::Initialize(collection);
	DataTable = LoadObject<UDataTable>(nullptr, (TCHAR*)(*SAVEDATAPATH));
	if (DataTable && CheckSave(DataTable, SAVENAME)) SaveData = DataTable->FindRow<FSaveData>(SAVENAME, TEXT(""));
}

void USaveManager::Deinitialize()
{
	Super::Deinitialize();
}

bool USaveManager::CheckSave(const UDataTable* Data, const FName& SaveName)
{
	return Data->FindRow<FSaveData>(SaveName, TEXT("")) ? true : false;
}
