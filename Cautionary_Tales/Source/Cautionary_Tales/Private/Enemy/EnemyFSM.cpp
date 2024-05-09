// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy/EnemyFSM.h"
#include "Enemy/BaseState.h"
#include "Enemy/ChaseState.h"
#include "Enemy/IdleState.h"
#include "Enemy/SearchState.h"



UEnemyFSM::UEnemyFSM()
{
	Idle = NewObject<UIdleState>();
	Chase = NewObject<UChaseState>();
	Search = NewObject<USearchState>();

	ChangeState(States::Idle);
}

void UEnemyFSM::ChangeState(States state)
{
	switch (state)
	{
	case States::Idle:
		CurrentState = Idle;
		CurrentState->EnterState();
		break;
	case States::Chasing:
		break;
	case States::Search:
		break;
	default:
		break;
	}
}

void UEnemyFSM::UpdateState(void)
{
}
