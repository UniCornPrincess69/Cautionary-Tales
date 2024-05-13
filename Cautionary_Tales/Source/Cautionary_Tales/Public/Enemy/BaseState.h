// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "BaseState.generated.h"

/**
 * 
 */
UCLASS(abstract)
class CAUTIONARY_TALES_API UBaseState : public UObject
{
	GENERATED_BODY()


public:
	virtual void SetFSM(class UEnemyFSM* fsm) {};
	virtual void EnterState(void) {};
	virtual void UpdateState(void) {};
	virtual void ExitState(void) {};
};
