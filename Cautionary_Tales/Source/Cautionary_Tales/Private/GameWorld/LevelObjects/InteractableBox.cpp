// Fill out your copyright notice in the Description page of Project Settings.


#include "GameWorld/LevelObjects/InteractableBox.h"
#include "Components/BoxComponent.h"
#include "GameWorld/LevelScriptActors/Game.h"
#include "Engine/TriggerBox.h"

// Sets default values
AInteractableBox::AInteractableBox()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
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
		Box = GetComponentByClass<UBoxComponent>();
		if (Box) Box->OnComponentBeginOverlap.AddUniqueDynamic(this, &AInteractableBox::OnBeginOverlap);
	}
}

void AInteractableBox::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	if (Box) Box->OnComponentBeginOverlap.RemoveDynamic(this, &AInteractableBox::OnBeginOverlap);
}

// Called every frame
void AInteractableBox::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AInteractableBox::OnBeginOverlap(UPrimitiveComponent* Overlap, AActor* Other, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (Other->IsA(ATriggerBox::StaticClass()))
	{
		OnTriggerActivated.Broadcast();
	}
}


