// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Enemy/BaseState.h"
#include "ChaseState.generated.h"

/**
 * 
 */
class AStruwwelController;
UCLASS()
class CAUTIONARY_TALES_API UChaseState : public UBaseState
{
	GENERATED_BODY()

public:
	// Inherited via UBaseState
	inline virtual void SetFSM(AStruwwelController* fsm) override { FSM = fsm; };

	virtual void EnterState(void) override;

	virtual void UpdateState(float deltaTime) override;

	virtual void ExitState(void) override;

private:

	AStruwwelController* FSM = nullptr;
	class ATestCharacter* Player = nullptr;
	class AStruwwel* Struwwel = nullptr;

	const float NORMALDISTANCE = 350.f;
	const float NORMALSPEED = 300.f;
	const float FASTWALKSPEED = 600.f;
};
