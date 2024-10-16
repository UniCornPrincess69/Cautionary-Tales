// Fill out your copyright notice in the Description page of Project Settings.


#include "GameWorld/LevelObjects/ProgressSpotLight.h"
#include "Components/SpotLightComponent.h"
#include "GameWorld/LevelScriptActors/Game.h"
#include "GameWorld/LevelObjects/InteractableBox.h"
// Sets default values
AProgressSpotLight::AProgressSpotLight()
{
	SpotLight = CreateDefaultSubobject<USpotLightComponent>(TEXT("SpotLight"));

}

// Called when the game starts or when spawned
void AProgressSpotLight::BeginPlay()
{
	Super::BeginPlay();
	auto world = GetWorld();
	if (world)
	{
		Game = Cast<AGame>(world->GetLevelScriptActor());
		Game->SetProgressSpotLight(this);
		Game->OnLevelLoaded.AddUniqueDynamic(this, &AProgressSpotLight::GetBoxCallback);
	}

	SpotLight->SetVisibility(false);
}

void AProgressSpotLight::EndPlay(const EEndPlayReason::Type endPlayReason)
{
	Super::EndPlay(endPlayReason);
	if (Box) Box->OnTriggerActivated.RemoveDynamic(this, &AProgressSpotLight::ActivateSpotLight);
	if (Game) Game->OnLevelLoaded.RemoveDynamic(this, &AProgressSpotLight::GetBoxCallback);
}

void AProgressSpotLight::ActivateSpotLight()
{
	SpotLight->SetVisibility(true);
}

void AProgressSpotLight::GetBoxCallback()
{
	Box = Game->GetInteractableBox();
	Box->OnTriggerActivated.AddUniqueDynamic(this, &AProgressSpotLight::ActivateSpotLight);
}


