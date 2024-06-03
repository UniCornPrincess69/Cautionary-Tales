// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy/SearchState.h"
#include "Enemy/StruwwelController.h"

void USearchState::EnterState(void)
{
	GEngine->AddOnScreenDebugMessage(-1, .5f, FColor::Black, TEXT("Searching..."));
	FSM->StopMovement();
}

void USearchState::UpdateState(void)
{
}

void USearchState::ExitState(void)
{
}
