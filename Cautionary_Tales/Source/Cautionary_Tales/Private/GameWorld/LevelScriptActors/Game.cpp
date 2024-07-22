// Fill out your copyright notice in the Description page of Project Settings.


#include "GameWorld/LevelScriptActors/Game.h"
#include "Kismet/GameplayStatics.h"
#include "GameWorld/TeleporterZone.h"
#include "Player/TestCharacter.h"
#include "Managers/GameManager.h"
#include "Managers/SaveManager.h"
#include "GameWorld/SaveData/SaveData.h"

void AGame::UpdateTeleporter(ATeleporterZone* newZone)
{
	TeleportZone = newZone;
	TeleportPlayer();
}

void AGame::BeginPlay()
{
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
}

void AGame::EndPlay(const EEndPlayReason::Type endPlayReason)
{
	Super::EndPlay(endPlayReason);
	//Player->OnTriggerOverlap.RemoveDynamic(this, &AGame::TeleportPlayer);
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
	//Player->OnTriggerOverlap.AddUniqueDynamic(this, &AGame::TeleportPlayer);
}
