// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy/ChaseState.h"
#include "Enemy/EnemyFSM.h"

void UChaseState::UpdateState(void)
{
	GEngine->AddOnScreenDebugMessage(-1, .3f, FColor::Black, TEXT("Chase State update"));
}

void UChaseState::ExitState(void)
{
}

void UChaseState::EnterState(void)
{
	GEngine->AddOnScreenDebugMessage(-1, .3f, FColor::Cyan, TEXT("Chase State entered"));
}
