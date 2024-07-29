// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy/AttackState.h"
#include "Player/TestCharacter.h"
#include "Enemy/StruwwelController.h"
#include "Enemy/Struwwel.h"

void UAttackState::EnterState(void)
{
	FSM->PlayAnimation();
	FSM->GetEnemy()->PlayerCaught();

}

void UAttackState::UpdateState(float deltaTime)
{
}

void UAttackState::ExitState(void)
{
}

