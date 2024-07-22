// Fill out your copyright notice in the Description page of Project Settings.


#include "GameWorld/LevelScriptActors/LevelScriptActor_Level_03.h"
#include "GameWorld/TeleporterZone.h"
#include "Kismet/GameplayStatics.h"
#include "GameWorld/LevelScriptActors/Game.h"

void ALevelScriptActor_Level_03::BeginPlay()
{
	auto world = GetWorld();
	auto actor = UGameplayStatics::GetActorOfClass(world, ATeleporterZone::StaticClass());
	TPZone = Cast<ATeleporterZone>(actor);

	auto level = world->GetLevelScriptActor();
	Game = Cast<AGame>(level);
	if (Game) Game->UpdateTeleporter(TPZone);
}

void ALevelScriptActor_Level_03::EndPlay(const EEndPlayReason::Type endPlayReason)
{
	Super::EndPlay(endPlayReason);
}
