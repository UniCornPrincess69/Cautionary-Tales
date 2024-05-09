// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Enemy/BaseState.h"
#include "ChaseState.generated.h"

/**
 * 
 */
UCLASS()
class CAUTIONARY_TALES_API UChaseState : public UBaseState
{
	GENERATED_BODY()

public:
	virtual void EnterState() override;
	virtual void UpdateState() override;
	virtual void ExitState() override;
	
};
