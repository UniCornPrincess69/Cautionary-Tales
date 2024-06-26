// Fill out your copyright notice in the Description page of Project Settings.


#include "GameWorld/TeleporterZone.h"
#include "Components/BoxComponent.h"

// Sets default values
ATeleporterZone::ATeleporterZone()
{
	Box = CreateDefaultSubobject<UBoxComponent>(TEXT("Teleport"));
	RootComponent = Box;
	
}



