// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Enemy/BaseState.h"
#include "SearchState.generated.h"

/**
 * 
 */
class AStruwwelController;
UCLASS()
class CAUTIONARY_TALES_API USearchState : public UBaseState
{
	GENERATED_BODY()

public:
	inline virtual void SetFSM(class AStruwwelController* fsm) override { FSM = fsm; };
	virtual void EnterState(void) override;
	virtual void UpdateState(float deltaTime) override;
	virtual void ExitState(void) override;

private:
	FVector GetRandomPointInRadius(float radius);

	AStruwwelController* FSM = nullptr;
	class AStruwwel* Struwwel = nullptr;
	class UNavigationSystemV1* NavSys = nullptr;

	float SearchTime = 5.f;
	float SearchCooldown = 0.f;
};
