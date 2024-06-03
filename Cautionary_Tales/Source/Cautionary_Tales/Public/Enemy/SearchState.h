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
	virtual void UpdateState(void) override;
	virtual void ExitState(void) override;

private:

	AStruwwelController* FSM = nullptr;

};
