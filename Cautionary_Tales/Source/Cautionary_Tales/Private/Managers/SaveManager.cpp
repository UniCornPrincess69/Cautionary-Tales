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
				FString jsonString;
				FJsonObjectConverter::UStructToJsonObjectString(saveData, jsonString);

				FString FilePath = SAVEPATH;

				if (FFileHelper::SaveStringToFile(jsonString, *FilePath))
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


void USaveManager::Initialize(FSubsystemCollectionBase& collection)
{
	Super::Initialize(collection);
	DataTable = LoadObject<UDataTable>(nullptr, (TCHAR*)(*DATATABLEPATH));

	if (DataTable)
	{
		if (DataExists(SAVEPATH))
		{
			if (CheckSave(DataTable, SAVENAME)) DataTable->RemoveRow(SAVENAME);

			FString dataString;
			if (FFileHelper::LoadFileToString(dataString, *SAVEPATH))
			{
				FSaveData deserializedData;
				FJsonObjectConverter::JsonObjectStringToUStruct(dataString, &deserializedData);
				DataTable->AddRow(SAVENAME, deserializedData);
			}
		}
		else UE_LOG(LogTemp, Warning, TEXT("File doesn't exist"));
	}

	if (DataTable && CheckSave(DataTable, SAVENAME)) SaveData = DataTable->FindRow<FSaveData>(SAVENAME, TEXT(""));
	else
	{
		DataTable->AddRow(SAVENAME, FSaveData());
	}

}

void USaveManager::Deinitialize()
{
	Super::Deinitialize();
}

bool USaveManager::CheckSave(const UDataTable* Data, const FName& SaveName)
{
	return Data->FindRow<FSaveData>(SaveName, TEXT("")) ? true : false;
}

bool USaveManager::DataExists(const FString& Path)
{
	return FPlatformFileManager::Get().GetPlatformFile().FileExists(*Path);
}
