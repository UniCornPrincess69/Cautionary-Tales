// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy/IdleState.h"
#include "Enemy/EnemyFSM.h"

void UIdleState::EnterState()
{
	//GEngine->AddOnScreenDebugMessage(-1, .5f, FColor::Red, TEXT("IdleState"));
}

void UIdleState::UpdateState()
{
	//GEngine->AddOnScreenDebugMessage(-1, .3f, FColor::Blue, TEXT("IdleUpdated"));
}

void UIdleState::ExitState()
{
}
