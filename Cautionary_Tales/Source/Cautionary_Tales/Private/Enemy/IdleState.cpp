// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy/IdleState.h"
#include "Enemy/StruwwelController.h"

void UIdleState::EnterState(void)
{
	GEngine->AddOnScreenDebugMessage(-1, .5f, FColor::Red, TEXT("IdleState"));
}

void UIdleState::UpdateState(float deltaTime)
{
	//GEngine->AddOnScreenDebugMessage(-1, .3f, FColor::Blue, TEXT("IdleUpdated"));
}

void UIdleState::ExitState(void)
{
}
