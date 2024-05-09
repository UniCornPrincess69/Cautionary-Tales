// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy/IdleState.h"

void UIdleState::EnterState()
{
	UE_LOG(LogTemp, Warning, TEXT("IdleState entered"));
}

void UIdleState::UpdateState()
{
}

void UIdleState::ExitState()
{
}
