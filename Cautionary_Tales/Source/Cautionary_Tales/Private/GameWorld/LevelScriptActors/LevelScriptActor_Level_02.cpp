// Fill out your copyright notice in the Description page of Project Settings.


#include "GameWorld/LevelScriptActors/LevelScriptActor_Level_02.h"
#include "Managers/LevelManager.h"
#include "GameWorld/TeleporterZone.h"
#include "GameWorld/LevelScriptActors/Game.h"
#include "Kismet/GameplayStatics.h"
#include "Managers/GameManager.h"

ALevelScriptActor_Level_02::ALevelScriptActor_Level_02()
{
	if (GetWorld())
	{
		auto gm = UGameManager::Instantiate(*this);
		LevelManager = gm->GetLevelManager();
		
		/*auto LM = GetWorld()->GetSubsystem<ULevelManager>();
		if (LM) LM->SetLevelTwo(this);*/
	}
}

void ALevelScriptActor_Level_02::BeginPlay()
{
	auto world = GetWorld();
	auto actor = UGameplayStatics::GetActorOfClass(world, ATeleporterZone::StaticClass());
	TPZone = Cast<ATeleporterZone>(actor);

	auto level = world->GetLevelScriptActor();
	Game = Cast<AGame>(level);
	if (Game) Game->UpdateTeleporter(TPZone);
	
}
