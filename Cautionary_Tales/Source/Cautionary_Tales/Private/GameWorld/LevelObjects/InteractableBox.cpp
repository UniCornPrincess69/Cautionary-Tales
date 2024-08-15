// Fill out your copyright notice in the Description page of Project Settings.


#include "GameWorld/LevelObjects/InteractableBox.h"
#include "Components/BoxComponent.h"
#include "GameWorld/LevelScriptActors/Game.h"

// Sets default values
AInteractableBox::AInteractableBox()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Box = CreateDefaultSubobject<UBoxComponent>(TEXT("Box"));
	SetRootComponent(Box);
	//TODO: OnBeginOverlap to react to trigger box and progression
}

// Called when the game starts or when spawned
void AInteractableBox::BeginPlay()
{
	Super::BeginPlay();
	auto world = GetWorld();
	if (world)
	{
		Game = Cast<AGame>(world->GetLevelScriptActor());
		Game->SetInteractableBox(this);
	}
}

// Called every frame
void AInteractableBox::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

