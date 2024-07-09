// Fill out your copyright notice in the Description page of Project Settings.


#include "GameWorld/LevelScriptActors/Game.h"
#include "Kismet/GameplayStatics.h"
#include "GameWorld/TeleporterZone.h"
#include "Player/TestCharacter.h"
#include "Managers/GameManager.h"

void AGame::BeginPlay()
{
	UGameplayStatics::LoadStreamLevel(this, "Level_01", true, false, FLatentActionInfo());
	

	auto teleport = UGameplayStatics::GetActorOfClass(GetWorld(), ATeleporterZone::StaticClass());
	TeleportZone = Cast<ATeleporterZone>(teleport);

	Manager = UGameManager::Instantiate(*this);
	if (Manager) Manager->OnPlayerReady.AddUniqueDynamic(this, &AGame::PlayerReady);

	UE_LOG(LogTemp, Warning, TEXT("Teleporter: %s"), *TeleportZone->GetName());
}

void AGame::EndPlay(const EEndPlayReason::Type endPlayReason)
{
	Super::EndPlay(endPlayReason);
	Player->OnTriggerOverlap.RemoveDynamic(this, &AGame::TeleportPlayer);
	Manager->OnPlayerReady.RemoveDynamic(this, &AGame::PlayerReady);
}

void AGame::TeleportPlayer(void)
{
	Player->SetActorLocation(TeleportZone->GetActorLocation());
}

void AGame::PlayerReady(ATestCharacter* player)
{
	Player = player;
	Player->OnTriggerOverlap.AddUniqueDynamic(this, &AGame::TeleportPlayer);
}
