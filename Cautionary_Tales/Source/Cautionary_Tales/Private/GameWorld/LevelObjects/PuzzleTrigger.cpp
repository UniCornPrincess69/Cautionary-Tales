// Fill out your copyright notice in the Description page of Project Settings.


#include "GameWorld/LevelObjects/PuzzleTrigger.h"
#include "Components/BoxComponent.h"
#include "GameWorld/LevelScriptActors/Game.h"

// Sets default values
APuzzleTrigger::APuzzleTrigger()
{
	TriggerBox = CreateDefaultSubobject<UBoxComponent>(TEXT("LightTrigger"));
}

void APuzzleTrigger::BeginPlay()
{
	Super::BeginPlay();
	auto world = GetWorld();
	if (world)
	{
		Game = Cast<AGame>(world->GetLevelScriptActor());
		Game->SetPuzzleTrigger(this);
	}
}



