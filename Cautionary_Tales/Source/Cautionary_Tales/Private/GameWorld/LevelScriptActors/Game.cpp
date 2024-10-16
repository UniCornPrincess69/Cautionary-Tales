// Fill out your copyright notice in the Description page of Project Settings.


#include "GameWorld/LevelScriptActors/Game.h"
#include "Kismet/GameplayStatics.h"
#include "GameWorld/TeleporterZone.h"
#include "Player/TestCharacter.h"
#include "Managers/GameManager.h"
#include "Managers/SaveManager.h"
#include "GameWorld/SaveData/SaveData.h"
#include "GameWorld/LevelObjects/InteractableBox.h"
#include "GameWorld/LevelObjects/ProgressionTrigger.h"
#include "GameWorld/LevelObjects/ProgressSpotLight.h"
#include "GameWorld/LevelObjects/PuzzleSpotLight.h"
#include "GameWorld/LevelObjects/PuzzleTrigger.h"


void AGame::UpdateTeleporter(ATeleporterZone* newZone)
{
	TeleportZone = newZone;
	TeleportPlayer();
}

void AGame::BeginPlay()
{
	Super::BeginPlay();
	Manager = UGameManager::Instantiate(*this);
	if (Manager) Manager->OnPlayerReady.AddUniqueDynamic(this, &AGame::PlayerReady);

	if (Manager->GetNewGameBool())
	{
		UGameplayStatics::LoadStreamLevel(this, FIRSTLEVEL, true, true, FLatentActionInfo());
	}
	else
	{
		//SaveManager = Manager->GetSaveManager();
		auto saveData = *GetWorld()->GetSubsystem<USaveManager>()->LoadGame();
		UGameplayStatics::LoadStreamLevel(this, FName(saveData.StreamingLevelName), true, true, FLatentActionInfo());
	}
	GetWorld()->GetTimerManager().SetTimer(TimerHandle, FTimerDelegate::CreateUObject(this, &AGame::LevelLoaded), 1.f, false, 2.5f);
}

void AGame::EndPlay(const EEndPlayReason::Type endPlayReason)
{
	Super::EndPlay(endPlayReason);
	Manager->OnPlayerReady.RemoveDynamic(this, &AGame::PlayerReady);
}

void AGame::TeleportPlayer(void)
{
	if(Player) Player->SetActorLocation(TeleportZone->GetActorLocation());
	else
	{
		Player = Manager->GetPlayer();
		Player->SetActorLocation(TeleportZone->GetActorLocation());
	}
	//TeleportZone->Destroy();
}

void AGame::PlayerReady(ATestCharacter* player)
{
	Player = player;
}

void AGame::LevelLoaded()
{
	OnLevelLoaded.Broadcast();
	GetWorld()->GetTimerManager().ClearTimer(TimerHandle);
}
