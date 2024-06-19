// Fill out your copyright notice in the Description page of Project Settings.


#include "GameWorld/States/CautionaryTalesGameState.h"

void ACautionaryTalesGameState::SetState(EGameState state)
{
	CurrentState = state;
	OnStateChange.Broadcast(CurrentState);
}
