// Fill out your copyright notice in the Description page of Project Settings.


#include "Managers/UIManager.h"
#include <Runtime/Engine/Classes/Kismet/GameplayStatics.h>
#include "Managers/GameManager.h"
#include "UI/InGameUI.h"
#include "Managers/SaveManager.h"
#include "Managers/LevelManager.h"


void UUIManager::StartGame(const UObject* target, const bool& IsNewGame)
{
	auto world = target->GetWorld();
	if (world) world->GetSubsystem<ULevelManager>()->LoadGame(IsNewGame);
}


void UUIManager::QuitGame(const UObject* target)
{
	UKismetSystemLibrary::QuitGame(target->GetWorld(), target->GetWorld()->GetFirstPlayerController(), EQuitPreference::Quit, true);
}

void UUIManager::QuitAndSave(const UObject* Target)
{
	auto save = GetWorld()->GetSubsystem<USaveManager>();
	if(save) save->SaveGame();
	QuitGame(Target);
}

void UUIManager::PauseGame(const UObject* target, bool isPaused)
{
	auto player = GetWorld()->GetFirstPlayerController();
	auto hud = Cast<AInGameUI>(player->GetHUD());


	if (isPaused)
	{
		if (player->IsPaused())
		{
			hud->InitWidgets();
			player->SetPause(!isPaused);
		}
		else
		{
			hud->SetPauseWidget();
			player->SetPause(isPaused);
		}
	}
}

void UUIManager::DeathScreen(const UObject* target)
{
}

void UUIManager::ToMainMenu(const UObject* target)
{
	auto save = GetWorld()->GetSubsystem<USaveManager>();
	if (save) save->SaveGame();
	
	auto world = GetWorld();

	if (world) UGameplayStatics::OpenLevel(world, MAIN_MENU, true);
}

void UUIManager::Initialize(FSubsystemCollectionBase& collection)
{
	Super::Initialize(collection);
}

void UUIManager::Deinitialize()
{
	Super::Deinitialize();
}
