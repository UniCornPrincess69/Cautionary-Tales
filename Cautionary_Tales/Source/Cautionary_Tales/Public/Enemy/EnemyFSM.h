// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "EnemyFSM.generated.h"

/**
 * 
 */
enum class States
{
	Idle,
	Chasing,
	Search
};

class UBaseState;
UCLASS()
class CAUTIONARY_TALES_API UEnemyFSM : public UObject
{
	GENERATED_BODY()
public:
	UEnemyFSM();
	void ChangeState(States state);
	void UpdateState(void);


private:
	UBaseState* CurrentState;
	UBaseState* Idle = nullptr;
	UBaseState* Chase = nullptr;
	UBaseState* Search = nullptr;

	
};
