// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Enemy/BaseState.h"
#include "IdleState.generated.h"

/**
 *
 */
class AStruwwelController;
UCLASS()
class CAUTIONARY_TALES_API UIdleState : public UBaseState
{
	GENERATED_BODY()


public:
	inline virtual void SetFSM(AStruwwelController* fsm) override { FSM = fsm; }

	virtual void EnterState() override;
	virtual void UpdateState() override;
	virtual void ExitState() override;

private:
	AStruwwelController* FSM = nullptr;
};
