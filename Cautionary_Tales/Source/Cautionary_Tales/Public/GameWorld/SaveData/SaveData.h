// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "SaveData.generated.h"

/**
 * 
 */

USTRUCT(BlueprintType)
struct CAUTIONARY_TALES_API FSaveData : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FVector PlayerPosition;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FName LevelName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FVector EnemyPosition;
};
