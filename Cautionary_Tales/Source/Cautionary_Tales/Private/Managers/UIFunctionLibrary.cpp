// Fill out your copyright notice in the Description page of Project Settings.


#include "Managers/UIFunctionLibrary.h"
#include "Managers/GameManager.h"
#include "Managers/UIManager.h"
#include <Runtime/Engine/Classes/Kismet/GameplayStatics.h>

UUIManager* UUIFunctionLibrary::GetUIManager(const UObject* Target)
{
	if (!Target)
	{
		UE_LOG(LogTemp, Warning, TEXT("Target of Getter was nullptr"));
	}
	auto manager = Target->GetWorld()->GetSubsystem<UUIManager>();
	
	return manager;
}

void UUIFunctionLibrary::StartGame(const UObject* GameTarget, const bool& IsNewGame)
{
	GetUIManager(GameTarget)->StartGame(GameTarget, IsNewGame);
}

void UUIFunctionLibrary::QuitFromMenu(const UObject* GameTarget)
{
	GetUIManager(GameTarget)->QuitGame(GameTarget);
}

void UUIFunctionLibrary::QuitFromGame(const UObject* GameTarget)
{
	GetUIManager(GameTarget)->QuitAndSave(GameTarget);
}

void UUIFunctionLibrary::ToMainMenu(const UObject* GameTarget)
{
	GetUIManager(GameTarget)->ToMainMenu(GameTarget);
}

void UUIFunctionLibrary::RestartCheckpoint(const UObject* GameTarget)
{
	//TODO: Restart from a given Checkpoint, needs save system
}

void UUIFunctionLibrary::ResumeGame(const UObject* GameTarget, bool IsClicked)
{
	GetUIManager(GameTarget)->PauseGame(GameTarget, IsClicked);
}
