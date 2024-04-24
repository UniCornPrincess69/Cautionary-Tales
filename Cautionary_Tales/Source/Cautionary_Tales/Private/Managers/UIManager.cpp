// Fill out your copyright notice in the Description page of Project Settings.


#include "Managers/UIManager.h"
#include <Runtime/Engine/Classes/Kismet/GameplayStatics.h>
#include "Managers/GameManager.h"
#include "UI/InGameUI.h"


void UUIManager::StartGame(const UObject* target)
{
	auto world = target->GetWorld();
	if (world) UGameplayStatics::OpenLevel(world, LEVEL_ONE, true);
	else GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Red, TEXT("Level not found"));
}

void UUIManager::QuitGame(const UObject* target)
{
	UKismetSystemLibrary::QuitGame(target->GetWorld(), target->GetWorld()->GetFirstPlayerController(), EQuitPreference::Quit, true);
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
	auto world = GetWorld();

	if (world) UGameplayStatics::OpenLevel(world, MAIN_MENU, true);
}
