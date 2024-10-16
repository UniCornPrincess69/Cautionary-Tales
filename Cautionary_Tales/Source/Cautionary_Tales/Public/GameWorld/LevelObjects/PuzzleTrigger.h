// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PuzzleTrigger.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnLightTriggered);
UCLASS()
class CAUTIONARY_TALES_API APuzzleTrigger : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APuzzleTrigger();

protected:
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type endPlayReason) override;

private:
	UFUNCTION()
		void OnBeginOverlap(UPrimitiveComponent* Overlap, AActor* Other, UPrimitiveComponent* OtherComp,
			int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

public:
	FOnLightTriggered OnLightTriggered;
private:
	class AGame* Game = nullptr;
	class UBoxComponent* TriggerBox = nullptr;
	bool WasTriggered = false;
};
