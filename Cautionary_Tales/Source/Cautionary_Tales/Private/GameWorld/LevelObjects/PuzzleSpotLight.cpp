// Fill out your copyright notice in the Description page of Project Settings.


#include "GameWorld/LevelObjects/PuzzleSpotLight.h"
#include "Components/SpotLightComponent.h"
#include "GameWorld/LevelScriptActors/Game.h"
#include "GameWorld/LevelObjects/InteractableBox.h"
#include "GameWorld/LevelObjects/PuzzleTrigger.h"

// Sets default values
APuzzleSpotLight::APuzzleSpotLight()
{
	SpotLight = CreateDefaultSubobject<USpotLightComponent>(TEXT("Puzzle Spotlight"));
}

// Called when the game starts or when spawned
void APuzzleSpotLight::BeginPlay()
{
	Super::BeginPlay();

	auto world = GetWorld();
	if (world)
	{
		Game = Cast<AGame>(world->GetLevelScriptActor());
		Game->SetPuzzleSpotLight(this);
		Game->OnLevelLoaded.AddUniqueDynamic(this, &APuzzleSpotLight::LevelLoadedCallback);
	}

	SpotLight->SetVisibility(false);

}

void APuzzleSpotLight::EndPlay(const EEndPlayReason::Type endPlayReason)
{
	if (Box) Box->OnTriggerActivated.RemoveDynamic(this, &APuzzleSpotLight::TriggerActivated);
	if (PuzzleTrigger) PuzzleTrigger->OnLightTriggered.RemoveDynamic(this, &APuzzleSpotLight::LightTriggerCallback);
	if (Game) Game->OnLevelLoaded.RemoveDynamic(this, &APuzzleSpotLight::LevelLoadedCallback);
}

void APuzzleSpotLight::LightTriggerCallback()
{
	SpotLight->SetVisibility(true);
}

void APuzzleSpotLight::TriggerActivated()
{
	SpotLight->SetVisibility(false);
}

void APuzzleSpotLight::LevelLoadedCallback()
{
	Box = Game->GetInteractableBox();
	Box->OnTriggerActivated.AddUniqueDynamic(this, &APuzzleSpotLight::TriggerActivated);
	PuzzleTrigger = Game->GetPuzzleTrigger();
	PuzzleTrigger->OnLightTriggered.AddUniqueDynamic(this, &APuzzleSpotLight::LightTriggerCallback);
}


