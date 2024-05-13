// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Enemy/BaseState.h"
#include "ChaseState.generated.h"

/**
 * 
 */
class UEnemyFSM;
UCLASS()
class CAUTIONARY_TALES_API UChaseState : public UBaseState
{
	GENERATED_BODY()

public:
	// Inherited via UBaseState
	FORCEINLINE virtual void SetFSM(UEnemyFSM* fsm) override { FSM = fsm; };

	virtual void EnterState(void) override;

	virtual void UpdateState(void) override;

	virtual void ExitState(void) override;

private:

	UEnemyFSM* FSM = nullptr;
};
