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
	void SaveGame(const FName& SaveName);
	FSaveData* LoadGame(const FName& SaveName);
	
private:
	virtual void Initialize(FSubsystemCollectionBase& collection) override;
	virtual void Deinitialize() override;
	bool CheckSave(const UDataTable* Data, const FName& SaveName);

	UDataTable* DataTable = nullptr;
	const FString SaveDataPath = FString(TEXT("/Game/Assets/Blueprints/DT_SaveData"));

};
