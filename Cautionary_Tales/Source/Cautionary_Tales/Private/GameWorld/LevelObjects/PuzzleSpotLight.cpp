// Fill out your copyright notice in the Description page of Project Settings.


#include "GameWorld/LevelObjects/PuzzleSpotLight.h"
#include "Components/SpotLightComponent.h"
#include "Managers/GameManager.h"
#include "Player/TestCharacter.h"
#include "GameWorld/LevelScriptActors/Game.h"
#include "GameWorld/LevelObjects/InteractableBox.h"

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
		Box = Game->GetInteractableBox();
		Box->OnTriggerActivated.AddUniqueDynamic(this, &APuzzleSpotLight::TriggerActivated);
	}

	SpotLight->SetVisibility(false);

	GM = UGameManager::Instantiate(*this);
	if (GM)
	{
		GM->OnPlayerReady.AddUniqueDynamic(this, &APuzzleSpotLight::PlayerReadyCallback);
	}
}

void APuzzleSpotLight::EndPlay(const EEndPlayReason::Type endPlayReason)
{
	if (Player) Player->OnLightTrigger.RemoveDynamic(this, &APuzzleSpotLight::LightTriggerCallback);
	if (GM) GM->OnPlayerReady.RemoveDynamic(this, &APuzzleSpotLight::PlayerReadyCallback);
	if (Box) Box->OnTriggerActivated.RemoveDynamic(this, &APuzzleSpotLight::TriggerActivated);
}

void APuzzleSpotLight::PlayerReadyCallback(ATestCharacter* player)
{
	Player = player;
	Player->OnLightTrigger.AddUniqueDynamic(this, &APuzzleSpotLight::LightTriggerCallback);
}

void APuzzleSpotLight::LightTriggerCallback()
{
	SpotLight->SetVisibility(true);
}

void APuzzleSpotLight::TriggerActivated()
{
	SpotLight->SetVisibility(false);
}


