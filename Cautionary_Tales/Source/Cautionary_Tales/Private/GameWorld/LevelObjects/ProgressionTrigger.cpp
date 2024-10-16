// Fill out your copyright notice in the Description page of Project Settings.


#include "GameWorld/LevelObjects/ProgressionTrigger.h"
#include "Components/BoxComponent.h"
#include "GameWorld/LevelScriptActors/Game.h"
#include "GameWorld/LevelObjects/InteractableBox.h"

// Sets default values
AProgressionTrigger::AProgressionTrigger()
{
	TriggerBox = CreateDefaultSubobject<UBoxComponent>(TEXT("TriggerBox"));
	TriggerBox->SetGenerateOverlapEvents(false);
}

void AProgressionTrigger::Instantiate(ELevels level)
{
	switch (level)
	{
	case ELevels::L_NONE:
		UE_LOG(LogTemp, Warning, TEXT("No level found"));
		break;
	case ELevels::L_ONE:
		LevelOneSetup();
		break;
	case ELevels::L_TWO:
		LevelTwoSetup();
		break;
	default:
		break;
	}
}

// Called when the game starts or when spawned
void AProgressionTrigger::BeginPlay()
{
	Super::BeginPlay();
	auto world = GetWorld();
	if (world)
	{
		Game = Cast<AGame>(world->GetLevelScriptActor());
		Game->SetProgressionTrigger(this);
	}
}

void AProgressionTrigger::EndPlay(EEndPlayReason::Type endPlayReason)
{
	if (InteractableBox) InteractableBox->OnTriggerActivated.RemoveDynamic(this, &AProgressionTrigger::SetTriggerActive);
}

void AProgressionTrigger::SetTriggerActive()
{
	TriggerBox->SetGenerateOverlapEvents(true);
}

void AProgressionTrigger::LevelOneSetup(void)
{
	TriggerBox->SetGenerateOverlapEvents(false);
	InteractableBox = Game->GetInteractableBox();
	InteractableBox->OnTriggerActivated.AddUniqueDynamic(this, &AProgressionTrigger::SetTriggerActive);
}

void AProgressionTrigger::LevelTwoSetup(void)
{
	TriggerBox->SetGenerateOverlapEvents(true);
}


