// Fill out your copyright notice in the Description page of Project Settings.


#include "GameWorld/LevelScriptActors/LevelScriptActor_Level_02.h"
#include "GameWorld/TeleporterZone.h"
#include "GameWorld/LevelScriptActors/Game.h"
#include "Kismet/GameplayStatics.h"
#include "Managers/GameManager.h"
#include "Managers/AudioManager.h"
#include "Sound/AmbientSound.h"
#include "GameWorld/LevelObjects/ProgressionTrigger.h"


void ALevelScriptActor_Level_02::BeginPlay()
{
	
	auto world = GetWorld();
	auto audio = UGameplayStatics::GetActorOfClass(world, AAmbientSound::StaticClass());
	if (world)
	{
		GM = UGameManager::Instantiate(*this);
		GM->GetAudioManager()->StopCurrentAmbient();
		GM->GetAudioManager()->SetCurrentAmbient(Cast<AAmbientSound>(audio));
	}
	auto actor = UGameplayStatics::GetActorOfClass(world, ATeleporterZone::StaticClass());
	TPZone = Cast<ATeleporterZone>(actor);

	auto level = world->GetLevelScriptActor();
	Game = Cast<AGame>(level);

	auto trigger = UGameplayStatics::GetActorOfClass(world, AProgressionTrigger::StaticClass());
	Trigger = Cast<AProgressionTrigger>(trigger);
	Trigger->Instantiate(ELevels::L_TWO);

	if (Game) Game->UpdateTeleporter(TPZone);
	
	TPZone->Destroy();
}

void ALevelScriptActor_Level_02::EndPlay(const EEndPlayReason::Type endPlayReason)
{
	Super::EndPlay(endPlayReason);
}
