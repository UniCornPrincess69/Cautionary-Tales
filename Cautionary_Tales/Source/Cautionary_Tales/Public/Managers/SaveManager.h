// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/WorldSubsystem.h"
#include "GameWorld/SaveData/VolumeData.h"
#include "SaveManager.generated.h"

/**
 * 
 */
struct FSaveData;
UCLASS()
class CAUTIONARY_TALES_API USaveManager : public UWorldSubsystem
{
	GENERATED_BODY()


public:
	void CreateSaveData(void);
	void SaveGame();
	FSaveData* LoadGame();
	void SaveVolumes(float master, float sfx, float music);
	FVolumeData* LoadVolume();
	
private:
	virtual void Initialize(FSubsystemCollectionBase& collection) override;
	virtual void Deinitialize() override;
	bool CheckSave(const UDataTable* Data, const FName& SaveName);
	bool CheckVolume(const UDataTable* Data, const FName& SaveName);
	bool DataExists(const FString& Path);
	FString GetSaveFilePath(void);
	FString GetVolumeFilePath(void);
	void CheckDirectory(void);
	FString GetStreamLevelName(void);
	void InitSaveData(void);
	void InitVolumeDate(void);

	FSaveData* SaveData = nullptr;
	FVolumeData* VolumeData = nullptr;
	UDataTable* SaveDataTable = nullptr;
	UDataTable* VolumeDataTable = nullptr;
	UGameManager* GM = nullptr;

	FVolumeData CurrentVolumeData;
	FSaveData CurrentSaveData;

	FString SavePath = FString(TEXT(""));
	FString VolumePath = FString(TEXT(""));

	const FString DEFAULTSAVENAME = FString(TEXT("SaveGame.json"));
	const FString DEFAULTVOLUMENAME = FString(TEXT("VolumeData.json"));
	const FString SAVETABLEPATH = FString(TEXT("/Game/Assets/Blueprints/DT_SaveData"));
	const FString VOLUMEDATAPATH = FString(TEXT("/Game/Assets/Blueprints/DT_VolumeData"));
	const FName SAVENAME = FName(TEXT("SAVE"));
	const FName VOLUMENAME = FName(TEXT("VOLUMES"));
};
