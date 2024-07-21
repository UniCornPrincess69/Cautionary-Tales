// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/WorldSubsystem.h"
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
	FSaveData CreateSaveData(void);
	void SaveGame();
	FSaveData* LoadGame();
	
private:
	virtual void Initialize(FSubsystemCollectionBase& collection) override;
	virtual void Deinitialize() override;
	bool CheckSave(const UDataTable* Data, const FName& SaveName);
	bool DataExists(const FString& Path);
	FString GetSaveFilePath(void);
	void CheckDirectory(void);
	FString GetStreamLevelName(void);

	FSaveData* SaveData = nullptr;
	UDataTable* DataTable = nullptr;
	UGameManager* GM = nullptr;

	FString SAVEPATH = FString(TEXT(""));
	const FString DATATABLEPATH = FString(TEXT("/Game/Assets/Blueprints/DT_SaveData"));
	const FName SAVENAME = FName(TEXT("SAVE"));

};
