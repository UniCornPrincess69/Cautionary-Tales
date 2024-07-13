// Fill out your copyright notice in the Description page of Project Settings.


#include "GameWorld/LevelScriptActors/LevelScriptActor_Level_01.h"
#include "Enemy/StruwwelController.h"
#include "NavigationSystem.h"
#include "Managers/LevelManager.h"
#include "Managers/GameManager.h"
#include "Kismet/GameplayStatics.h"
#include "GameWorld/TeleporterZone.h"
#include "GameWorld/LevelScriptActors/Game.h"

ALevelScriptActor_Level_01::ALevelScriptActor_Level_01()
{
	auto world = GetWorld();
	if (world)
	{
		auto gm = UGameManager::Instantiate(*this);
		LevelManager = gm->GetLevelManager();
		
		/*LevelManager = GetWorld()->GetSubsystem<ULevelManager>();
		if (LevelManager) LevelManager->SetLevelOne(this);*/
	}
}

void ALevelScriptActor_Level_01::BeginPlay()
{
	/*auto world = GetWorld();
	auto actor = UGameplayStatics::GetActorOfClass(world, ATeleporterZone::StaticClass());
	TPZone = Cast<ATeleporterZone>(actor);
	
	auto game = Cast<AGame>(world);
	game->UpdateTeleporter(TPZone);*/
	
	
	//LevelManager->SetCurrentLevel(LevelName);

}

void ALevelScriptActor_Level_01::EndPlay(const EEndPlayReason::Type endPlayReason)
{
	Super::EndPlay(endPlayReason);
}
