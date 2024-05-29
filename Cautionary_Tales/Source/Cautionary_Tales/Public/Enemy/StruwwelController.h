// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "StruwwelController.generated.h"

/**
 * 
 */
class UAIComponent;
UCLASS()
class CAUTIONARY_TALES_API AStruwwelController : public AAIController
{
	GENERATED_BODY()
	
public:
	inline void SetAIComponent(UAIComponent* component) { AIComponent = component; }

private:
	virtual void BeginPlay() override;

	virtual void OnPossess(APawn* pawn) override;

	UAIComponent* AIComponent = nullptr;
	class AStruwwel* Struwwel = nullptr;
};
