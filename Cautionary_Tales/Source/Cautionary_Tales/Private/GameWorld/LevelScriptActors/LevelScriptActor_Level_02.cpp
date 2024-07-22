// Fill out your copyright notice in the Description page of Project Settings.


#include "GameWorld/LevelScriptActors/LevelScriptActor_Level_02.h"
#include "GameWorld/TeleporterZone.h"
#include "GameWorld/LevelScriptActors/Game.h"
#include "Kismet/GameplayStatics.h"


void ALevelScriptActor_Level_02::BeginPlay()
{
	GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Red, TEXT("Level 2 loaded"));
	
	auto world = GetWorld();
	auto actor = UGameplayStatics::GetActorOfClass(world, ATeleporterZone::StaticClass());
	TPZone = Cast<ATeleporterZone>(actor);

	auto level = world->GetLevelScriptActor();
	Game = Cast<AGame>(level);
	if (Game) Game->UpdateTeleporter(TPZone);
	
	TPZone->Destroy();
}

void ALevelScriptActor_Level_02::EndPlay(const EEndPlayReason::Type endPlayReason)
{
	Super::EndPlay(endPlayReason);
}
