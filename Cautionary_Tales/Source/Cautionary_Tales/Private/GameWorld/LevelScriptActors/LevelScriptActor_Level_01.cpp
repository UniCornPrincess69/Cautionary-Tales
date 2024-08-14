// Fill out your copyright notice in the Description page of Project Settings.


#include "GameWorld/LevelScriptActors/LevelScriptActor_Level_01.h"
#include "Enemy/StruwwelController.h"
#include "NavigationSystem.h"
#include "Managers/LevelManager.h"
#include "Managers/GameManager.h"
#include "Kismet/GameplayStatics.h"
#include "GameWorld/TeleporterZone.h"
#include "GameWorld/LevelScriptActors/Game.h"
#include "Sound/AmbientSound.h"
#include "Managers/AudioManager.h"
#include "GameWorld/LevelObjects/ProgressionTrigger.h"

ALevelScriptActor_Level_01::ALevelScriptActor_Level_01()
{
	auto world = GetWorld();
	if (world)
	{
		Manager = UGameManager::Instantiate(*this);
		if (Manager) LevelManager = Manager->GetLevelManager();
		
		
		/*LevelManager = GetWorld()->GetSubsystem<ULevelManager>();
		if (LevelManager) LevelManager->SetLevelOne(this);*/
	}
}

void ALevelScriptActor_Level_01::BeginPlay()
{
	auto world = GetWorld();
	if (world)
	{
		Manager = UGameManager::Instantiate(*this);
		if (Manager)
		{
			LevelManager = Manager->GetLevelManager();
			auto sound = UGameplayStatics::GetActorOfClass(GetWorld(), AAmbientSound::StaticClass());
			Manager->GetAudioManager()->SetCurrentAmbient(Cast<AAmbientSound>(sound));
		}
		auto trigger = UGameplayStatics::GetActorOfClass(world, AProgressionTrigger::StaticClass());
		Trigger = Cast<AProgressionTrigger>(trigger);
		Trigger->Instantiate(ELevels::L_ONE);
	}
	/*auto sound = UGameplayStatics::GetActorOfClass(GetWorld(), AAmbientSound::StaticClass());
	Manager->GetAudioManager()->SetCurrentAmbient(Cast<AAmbientSound>(sound));*/
}

void ALevelScriptActor_Level_01::EndPlay(const EEndPlayReason::Type endPlayReason)
{
	Super::EndPlay(endPlayReason);
}
