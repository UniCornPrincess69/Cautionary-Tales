// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy/ChaseState.h"
#include "Player/TestCharacter.h"
#include "Enemy/StruwwelController.h"
#include "Enemy/Struwwel.h"


//TODO: Speed adjustment: Struwwel gets faster if further away to keep players on their toes!
void UChaseState::UpdateState(float deltaTime)
{
	auto playerLoc = Player->GetActorLocation();
	auto enemyLoc = Struwwel->GetActorLocation();
	auto distance = FVector::Distance(enemyLoc, playerLoc);
	if (distance <= 215.f)
	{
		FSM->StopMovement();
		FSM->SetState(EStates::ST_ATTACK);
	}
	else if (distance >= NORMALDISTANCE)
	{
		Struwwel->SetWalkSpeed(FASTWALKSPEED);
	}
	else Struwwel->SetWalkSpeed(NORMALSPEED);

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
