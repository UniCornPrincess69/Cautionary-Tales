// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "VolumeData.generated.h"

/**
 * 
 */
USTRUCT(BlueprintType)
struct CAUTIONARY_TALES_API FVolumeData : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float MasterVolume = 0.f;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float SFXVolume = 0.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float MusicVolume = 0.f;

};
