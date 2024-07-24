// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy/ChaseState.h"
#include "Player/TestCharacter.h"
#include "Enemy/StruwwelController.h"
#include "Enemy/Struwwel.h"



void UChaseState::UpdateState(float deltaTime)
{
	auto playerLoc = Player->GetActorLocation();
	auto enemyLoc = Struwwel->GetActorLocation();
	
	if (FVector::Distance(enemyLoc, playerLoc) <= 215.f)
	{
		FSM->StopMovement();
		FSM->SetState(EStates::ST_ATTACK);
	}
}

void UChaseState::ExitState(void)
{
	FSM->StopMovement();
}


void UChaseState::EnterState(void)
{
	Struwwel = FSM->GetEnemy();
	if (!Player)
	{
		Player = FSM->GetPlayer();
	}
	FSM->PlayAnimation();
	FSM->MoveToPlayer();

}
