// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy/EnemyFSM.h"
#include "Enemy/BaseState.h"
#include "Enemy/ChaseState.h"
#include "Enemy/IdleState.h"
#include "Enemy/SearchState.h"



UEnemyFSM::UEnemyFSM()
{
	Idle = NewObject<UIdleState>();
	Idle->SetFSM(this);
	Chase = NewObject<UChaseState>();
	Search = NewObject<USearchState>();

	ChangeState(EStates::ST_IDLE);
}

void UEnemyFSM::ChangeState(EStates state)
{
	if (CurrentState == state) return;
	if (ActiveState) ActiveState->ExitState();
	switch (state)
	{
	case EStates::ST_IDLE:
		CurrentState = EStates::ST_IDLE;
		ActiveState = Idle;
		break;
	case EStates::ST_CHASE:
		CurrentState = EStates::ST_CHASE;
		ActiveState = Chase;
		break;
	case EStates::ST_SEARCH:
		CurrentState = EStates::ST_SEARCH;
		ActiveState = Search;
		break;
	default:
		break;
	}

	ActiveState->EnterState();
}

void UEnemyFSM::UpdateState(void)
{
	ActiveState->UpdateState();
}
