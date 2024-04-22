// Fill out your copyright notice in the Description page of Project Settings.


#include "Managers/UIManager.h"
#include <Runtime/Engine/Classes/Kismet/GameplayStatics.h>
#include "Managers/GameManager.h"
#include "UI/InGameUI.h"


void UUIManager::StartGame(const UObject* Target)
{
	auto world = Target->GetWorld();
	if (world) UGameplayStatics::OpenLevel(world, "Level_01", true);
	else GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Red, TEXT("Level not found"));
}

void UUIManager::QuitGame(const UObject* Target)
{
	UKismetSystemLibrary::QuitGame(Target->GetWorld(), Target->GetWorld()->GetFirstPlayerController(), EQuitPreference::Quit, true);
}

void UUIManager::PauseGame(const UObject* Target, bool isPaused)
{
	auto player = GetWorld()->GetFirstPlayerController();
	auto hud = Cast<AInGameUI>(player->GetHUD());


	if (isPaused)
	{
		if (player->IsPaused())
		{
			hud->InitWidgets();
			player->SetPause(!isPaused);
			//isPaused = false;
		}
		else
		{
			hud->SetPauseWidget();
			player->SetPause(isPaused);
		}
	}
}

void UUIManager::DeathScreen(const UObject* Target)
{
}
