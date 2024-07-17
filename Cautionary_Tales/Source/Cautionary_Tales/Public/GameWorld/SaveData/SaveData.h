// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "Enemy/StruwwelController.h"
#include "SaveData.generated.h"

/**
 *
 */

USTRUCT(BlueprintType)
struct CAUTIONARY_TALES_API FSaveData : public FTableRowBase
{
	GENERATED_BODY()


	/*FORCEINLINE FSaveData(const FVector& PlayerPosition = FVector{0.f, 0.f, 0.f},
		const FName& LevelName = FName{TEXT("MainMenu")},
		const FVector& EnemyPosition = FVector{0.f, 0.f, 0.f});*/

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector PlayerPosition = FVector(0.f, 0.f, 0.f);

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString StreamingLevelName = FString(TEXT("None"));

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector EnemyPosition = FVector(0.f, 0.f, 0.f);

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EStates EnemyState = EStates::ST_NONE;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool IsEnemyActive = false;
};
