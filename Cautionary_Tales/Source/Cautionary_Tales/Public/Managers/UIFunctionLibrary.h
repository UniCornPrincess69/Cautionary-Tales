// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "UIFunctionLibrary.generated.h"

/**
 *
 */
UCLASS()
class CAUTIONARY_TALES_API UUIFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

		static class UUIManager* GetUIManager(const UObject* Target);

public:

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Start Game", Category = "UI Function"))
		static void StartGame(const UObject* GameTarget);

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Quit Game", Category = "UI Function"))
		static void QuitGame(const UObject* GameTarget);

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "To Main Menu", Category = "UI Function"))
		static void ToMainMenu(const UObject* GameTarget);

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Restart from Checkpoint", Category = "UI Function"))
		static void RestartCheckpoint(const UObject* GameTarget);
};
