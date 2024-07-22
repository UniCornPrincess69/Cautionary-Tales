// Fill out your copyright notice in the Description page of Project Settings.


#include "Managers/SaveManager.h"
#include "GameWorld/SaveData/SaveData.h"
#include "Managers/GameManager.h"
#include <Runtime/Engine/Classes/Kismet/GameplayStatics.h>
#include "Player/TestCharacter.h"
#include "Enemy/Struwwel.h"
#include "JsonObjectConverter.h"
#include "Serialization/JsonSerializer.h"
#include "Misc/FileHelper.h"
#include "Misc/Paths.h"



void USaveManager::CreateSaveData(void)
{
	if (GM && GetWorld())
	{
		CurrentSaveData.PlayerPosition = GM->GetPlayer()->GetActorLocation();
		CurrentSaveData.StreamingLevelName = GetStreamLevelName();
		if (GM->GetEnemyActive())
		{
			CurrentSaveData.EnemyPosition = GM->GetEnemy()->GetActorLocation();
			CurrentSaveData.EnemyState = GM->GetEnemy()->GetCurrentState();
			CurrentSaveData.IsEnemyActive = true;
		}
		else
		{
			CurrentSaveData.EnemyPosition = FVector(0.f, 0.f, 0.f);
			CurrentSaveData.EnemyState = EStates::ST_NONE;
			CurrentSaveData.IsEnemyActive = false;
		}
		//TODO: Get Enemy location, probably some more info. Adjust SaveData accordingly
	}

}

void USaveManager::SaveGame()
{
	if (!DataTable) UE_LOG(LogTemp, Error, TEXT("DataTable is not initialized"));
	
	if (DataTable)
	{
		CreateSaveData();

		if (!CheckSave(DataTable, SAVENAME))
		{
			DataTable->AddRow(SAVENAME, CurrentSaveData);
			UE_LOG(LogTemp, Log, TEXT("Adding new save data row"));
		}
		else
		{
			UE_LOG(LogTemp, Log, TEXT("Updating save data row"));
			DataTable->RemoveRow(SAVENAME);
			DataTable->AddRow(SAVENAME, CurrentSaveData);
			DataTable->Modify();
			//DataTable->MarkPackageDirty();

			if (!SaveData) UE_LOG(LogTemp, Log, TEXT("SaveData not initialized"));

			if (SaveData)
			{
				FString jsonString;
				FJsonObjectConverter::UStructToJsonObjectString(CurrentSaveData, jsonString);

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
	CheckDirectory();
	SAVEPATH = GetSaveFilePath();
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
	if (DataTable && CheckSave(DataTable, SAVENAME))
	{
		SaveData = DataTable->FindRow<FSaveData>(SAVENAME, TEXT(""));
	}
	else
	{
		DataTable->AddRow(SAVENAME, FSaveData());
	}

	GM = UGameManager::Instantiate(*this);
	if (GM) GM->SetSaveManager(this);
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

FString USaveManager::GetSaveFilePath(void)
{
	FString saveDir = FPaths::ProjectSavedDir();
	FString fileName = TEXT("SaveGame.json");
	return saveDir / fileName;
}

void USaveManager::CheckDirectory(void)
{
	FString saveDir = FPaths::ProjectSavedDir();
	if (!FPlatformFileManager::Get().GetPlatformFile().DirectoryExists(*saveDir))
	{
		FPlatformFileManager::Get().GetPlatformFile().CreateDirectory(*saveDir);
	}
}

FString USaveManager::GetStreamLevelName(void)
{
	FString levelName = FString(TEXT(""));
	auto streamLevels = GetWorld()->GetStreamingLevels();

	for (auto& streamingLevel : streamLevels)
	{
		if (streamingLevel && streamingLevel->IsLevelLoaded())
		{
			levelName = streamingLevel->GetWorldAssetPackageName();
		}
	}
	return levelName;
}
