// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "EnemyFSM.generated.h"

/**
 * 
 */
enum class EStates
{
	ST_NONE,
	ST_IDLE,
	ST_CHASE,
	ST_SEARCH
};

class UBaseState;
UCLASS()
class CAUTIONARY_TALES_API UEnemyFSM : public UObject
{
	GENERATED_BODY()
public:
	UEnemyFSM();
	void ChangeState(EStates state);
	void UpdateState(void);


private:
	EStates CurrentState = EStates::ST_NONE;
	UBaseState* ActiveState = nullptr;
	UBaseState* Idle = nullptr;
	UBaseState* Chase = nullptr;
	UBaseState* Search = nullptr;

	
};
