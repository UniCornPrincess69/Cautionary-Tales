// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PuzzleSpotLight.generated.h"

class ATestCharacter;
UCLASS()
class CAUTIONARY_TALES_API APuzzleSpotLight : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APuzzleSpotLight();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type endPlayReason) override;

private:

	UFUNCTION()
		void LightTriggerCallback();

	UFUNCTION()
		void TriggerActivated();

	UFUNCTION()
		void LevelLoadedCallback();

	UPROPERTY(EditAnywhere)
	class USpotLightComponent* SpotLight = nullptr;
	class AGame* Game = nullptr;
	class APuzzleTrigger* PuzzleTrigger = nullptr;
	class AInteractableBox* Box = nullptr;
};
