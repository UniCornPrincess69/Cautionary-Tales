// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PuzzleTrigger.generated.h"

UCLASS()
class CAUTIONARY_TALES_API APuzzleTrigger : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APuzzleTrigger();

protected:
	virtual void BeginPlay() override;

private:
	class AGame* Game = nullptr;
	class UBoxComponent* TriggerBox = nullptr;
};
