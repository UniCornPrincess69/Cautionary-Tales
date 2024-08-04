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
	}

}

void USaveManager::SaveGame()
{
	if (!SaveDataTable) UE_LOG(LogTemp, Error, TEXT("DataTable is not initialized"));
	
	SaveDataTable = LoadObject<UDataTable>(nullptr, (TCHAR*)(*SAVETABLEPATH));

	if (SaveDataTable)
	{
		CreateSaveData();

		if (!CheckSave(SaveDataTable, SAVENAME))
		{
			SaveDataTable->AddRow(SAVENAME, CurrentSaveData);
			UE_LOG(LogTemp, Log, TEXT("Adding new save data row"));
		}
		else
		{
			UE_LOG(LogTemp, Log, TEXT("Updating save data row"));
			SaveDataTable->RemoveRow(SAVENAME);
			SaveDataTable->AddRow(SAVENAME, CurrentSaveData);
			SaveDataTable->Modify();
			SaveDataTable->MarkPackageDirty();

			if (!SaveData) UE_LOG(LogTemp, Log, TEXT("SaveData not initialized"));

			if (SaveData)
			{
				FString jsonString;
				FJsonObjectConverter::UStructToJsonObjectString(CurrentSaveData, jsonString);

				FString FilePath = SavePath;

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
	if (!CheckSave(SaveDataTable, SAVENAME))
	{
		return nullptr;
	}
	else
	{
		return SaveData;
	}
}

void USaveManager::SaveVolumes(float master, float sfx, float music)
{
	if (GM && GetWorld())
	{
		CurrentVolumeData.MasterVolume = master;
		CurrentVolumeData.SFXVolume = sfx;
		CurrentVolumeData.MusicVolume = music;
		if (!CheckVolume(VolumeDataTable, VOLUMENAME))
		{
			VolumeDataTable->AddRow(VOLUMENAME, CurrentVolumeData);
			UE_LOG(LogTemp, Log, TEXT("Adding new save data row"));
		}
		else
		{
			UE_LOG(LogTemp, Log, TEXT("Updating save data row"));
			VolumeDataTable->RemoveRow(VOLUMENAME);
			VolumeDataTable->AddRow(VOLUMENAME, CurrentVolumeData);
			VolumeDataTable->Modify();
			VolumeDataTable->MarkPackageDirty();

			if (!VolumeData) UE_LOG(LogTemp, Log, TEXT("SaveData not initialized"));

			if (VolumeData)
			{
				FString jsonString;
				FJsonObjectConverter::UStructToJsonObjectString(CurrentVolumeData, jsonString);

				FString FilePath = VolumePath;

				if (FFileHelper::SaveStringToFile(jsonString, *FilePath))
				{
					UE_LOG(LogTemp, Warning, TEXT("Success"));
				}
				else UE_LOG(LogTemp, Warning, TEXT("Failed"));
			}
		}
	}

}

FVolumeData* USaveManager::LoadVolume()
{
	if (!CheckVolume(VolumeDataTable, VOLUMENAME))
	{
		return nullptr;
	}
	else return VolumeData;
}


void USaveManager::Initialize(FSubsystemCollectionBase& collection)
{
	Super::Initialize(collection);
	SaveDataTable = LoadObject<UDataTable>(nullptr, (TCHAR*)(*SAVETABLEPATH));
	VolumeDataTable = LoadObject<UDataTable>(nullptr, (TCHAR*)(*VOLUMEDATAPATH));
	CheckDirectory();

	InitSaveData();
	InitVolumeDate();

	GM = UGameManager::Instantiate(*this);
	if (GM) GM->SetSaveManager(this);
}

void USaveManager::Deinitialize()
{
	Super::Deinitialize();
}

bool USaveManager::CheckSave(const UDataTable* Data, const FName& SaveName)
{
	if (!Data) return false;
	return Data->FindRow<FSaveData>(SaveName, TEXT("")) ? true : false;
}

bool USaveManager::CheckVolume(const UDataTable* Data, const FName& SaveName)
{
	if (!Data) return false;
	return Data->FindRow<FVolumeData>(SaveName, TEXT("")) ? true : false;
}

bool USaveManager::DataExists(const FString& Path)
{
	return FPlatformFileManager::Get().GetPlatformFile().FileExists(*Path);
}

FString USaveManager::GetSaveFilePath(void)
{
	FString saveDir = FPaths::ProjectSavedDir();
	FString fileName = DEFAULTSAVENAME;
	return saveDir / fileName;
}

FString USaveManager::GetVolumeFilePath(void)
{
	FString saveDir = FPaths::ProjectSavedDir();
	FString fileName = DEFAULTVOLUMENAME;
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

void USaveManager::InitSaveData(void)
{
	SavePath = GetSaveFilePath();
	if (SaveDataTable)
	{
		if (DataExists(SavePath))
		{
			if (CheckSave(SaveDataTable, SAVENAME)) SaveDataTable->RemoveRow(SAVENAME);

			FString dataString;
			if (FFileHelper::LoadFileToString(dataString, *SavePath))
			{
				FSaveData deserializedData;
				FJsonObjectConverter::JsonObjectStringToUStruct(dataString, &deserializedData);
				SaveDataTable->AddRow(SAVENAME, deserializedData);
			}
		}
		else UE_LOG(LogTemp, Warning, TEXT("File doesn't exist"));
	}
	if (SaveDataTable && CheckSave(SaveDataTable, SAVENAME))
	{
		SaveData = SaveDataTable->FindRow<FSaveData>(SAVENAME, TEXT(""));
	}
	else
	{
		SaveDataTable->AddRow(SAVENAME, FSaveData());
	}

}

void USaveManager::InitVolumeDate(void)
{
	VolumePath = GetVolumeFilePath();
	if (VolumeDataTable)
	{
		if (DataExists(VolumePath))
		{
			if (CheckSave(VolumeDataTable, VOLUMENAME)) VolumeDataTable->RemoveRow(VOLUMENAME);

			FString dataString;
			if (FFileHelper::LoadFileToString(dataString, *VolumePath))
			{
				FSaveData deserializedData;
				FJsonObjectConverter::JsonObjectStringToUStruct(dataString, &deserializedData);
				VolumeDataTable->AddRow(VOLUMENAME, deserializedData);
			}
		}
		else UE_LOG(LogTemp, Warning, TEXT("File doesn't exist"));
	}
	if (VolumeDataTable && CheckVolume(VolumeDataTable, VOLUMENAME))
	{
		VolumeData = VolumeDataTable->FindRow<FVolumeData>(VOLUMENAME, TEXT(""));
	}
	else
	{
		VolumeDataTable->AddRow(VOLUMENAME, FVolumeData());
	}
}
