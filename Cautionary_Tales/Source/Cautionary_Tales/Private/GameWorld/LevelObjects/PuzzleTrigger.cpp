// Fill out your copyright notice in the Description page of Project Settings.


#include "GameWorld/LevelObjects/PuzzleTrigger.h"
#include "Components/BoxComponent.h"
#include "GameWorld/LevelScriptActors/Game.h"
#include "Player/TestCharacter.h"

// Sets default values
APuzzleTrigger::APuzzleTrigger()
{
	TriggerBox = CreateDefaultSubobject<UBoxComponent>(TEXT("LightTrigger"));
}

void APuzzleTrigger::BeginPlay()
{
	Super::BeginPlay();
	TriggerBox->OnComponentBeginOverlap.AddUniqueDynamic(this, &APuzzleTrigger::OnBeginOverlap);
	auto world = GetWorld();
	if (world)
	{
		Game = Cast<AGame>(world->GetLevelScriptActor());
		Game->SetPuzzleTrigger(this);
	}
}

void APuzzleTrigger::EndPlay(const EEndPlayReason::Type endPlayReason)
{
	Super::EndPlay(endPlayReason);
	if (TriggerBox) TriggerBox->OnComponentBeginOverlap.RemoveDynamic(this, &APuzzleTrigger::OnBeginOverlap);
}

void APuzzleTrigger::OnBeginOverlap(UPrimitiveComponent* Overlap, AActor* Other, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (Cast<ATestCharacter>(Other) && !WasTriggered)
	{
		OnLightTriggered.Broadcast();
		WasTriggered = true;
	}
}



