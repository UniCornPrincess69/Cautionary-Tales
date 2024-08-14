// Fill out your copyright notice in the Description page of Project Settings.


#include "GameWorld/LevelObjects/PuzzleTrigger.h"
#include "Components/BoxComponent.h"

// Sets default values
APuzzleTrigger::APuzzleTrigger()
{
	TriggerBox = CreateDefaultSubobject<UBoxComponent>(TEXT("LightTrigger"));
}



