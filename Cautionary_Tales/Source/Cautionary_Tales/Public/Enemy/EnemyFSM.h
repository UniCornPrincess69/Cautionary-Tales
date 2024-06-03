// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "EnemyFSM.generated.h"

/**
 * 
 */
//enum class EStates
//{
//	ST_NONE,
//	ST_IDLE,
//	ST_CHASE,
//	ST_SEARCH
//};

class UBaseState;
class APlayerCharacter;
class AStruwwel;
class AStruwwelController;
UCLASS()
class CAUTIONARY_TALES_API UEnemyFSM : public UObject
{
	GENERATED_BODY()

public:
	UEnemyFSM();
	//void ChangeState(EStates state);
	void UpdateState(void);

	//inline void SetPlayer(APlayerCharacter* player) { Player = player; }
	//inline void SetEnemy(AStruwwel* struwwel) { Struwwel = struwwel; }
	//inline void SetAIController(AStruwwelController* controller) { Controller = controller; }

	/*APlayerCharacter* GetPlayer(void);
	AStruwwel* GetEnemy(void);
	AStruwwelController* GetAIController(void);*/

private:
	/*EStates CurrentState = EStates::ST_NONE;
	UBaseState* ActiveState = nullptr;
	UBaseState* Idle = nullptr;
	UBaseState* Chase = nullptr;
	UBaseState* Search = nullptr;

	APlayerCharacter* Player = nullptr;
	AStruwwel* Struwwel = nullptr;
	AStruwwelController* Controller;*/
};
