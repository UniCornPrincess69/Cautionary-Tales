// Fill out your copyright notice in the Description page of Project Settings.


#include "GameWorld/LevelObjects/ProgressSpotLight.h"
#include "Components/SpotLightComponent.h"

// Sets default values
AProgressSpotLight::AProgressSpotLight()
{
	SpotLight = CreateDefaultSubobject<USpotLightComponent>(TEXT("SpotLight"));

}

// Called when the game starts or when spawned
void AProgressSpotLight::BeginPlay()
{
	Super::BeginPlay();
	SpotLight->SetVisibility(false);
}


