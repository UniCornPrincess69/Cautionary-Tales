// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ProgressSpotLight.generated.h"

UCLASS()
class CAUTIONARY_TALES_API AProgressSpotLight : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AProgressSpotLight();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type endPlayReason) override;
private:
	UFUNCTION()
		void ActivateSpotLight();

	UFUNCTION()
		void GetBoxCallback();


	UPROPERTY(EditAnywhere)
	class USpotLightComponent* SpotLight = nullptr;

	class AGame* Game = nullptr;
	class AInteractableBox* Box = nullptr;
};
