// Fill out your copyright notice in the Description page of Project Settings.


#include "GameWorld/LevelObjects/ProgressionTrigger.h"
#include "Components/BoxComponent.h"

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
	
}

void AProgressionTrigger::LevelOneSetup(void)
{
	//TriggerBox->SetGenerateOverlapEvents(false);
}

void AProgressionTrigger::LevelTwoSetup(void)
{
	GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Red, TEXT("Level Two setup"));

}


