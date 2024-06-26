// Fill out your copyright notice in the Description page of Project Settings.


#include "GameWorld/LevelScriptActors/LevelScriptActor_Level_01.h"
#include "Enemy/StruwwelController.h"
#include "NavigationSystem.h"
#include "Managers/LevelManager.h"

ALevelScriptActor_Level_01::ALevelScriptActor_Level_01()
{
	auto world = GetWorld();
	if (world)
	{
		auto LM = GetWorld()->GetSubsystem<ULevelManager>();
		if (LM) LM->SetLevelOne(this);
	}
}

void ALevelScriptActor_Level_01::BeginPlay()
{
}

void ALevelScriptActor_Level_01::EndPlay(const EEndPlayReason::Type endPlayReason)
{
	Super::EndPlay(endPlayReason);
}
