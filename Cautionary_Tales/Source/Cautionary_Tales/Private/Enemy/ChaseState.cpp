// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy/ChaseState.h"
#include "Player/PlayerCharacter.h"
#include "Enemy/StruwwelController.h"



void UChaseState::UpdateState(float deltaTime)
{


}

void UChaseState::ExitState(void)
{
	//GEngine->AddOnScreenDebugMessage(-1, .5f, FColor::Blue, TEXT("Chase exited"));
	FSM->StopMovement();
	
}


void UChaseState::EnterState(void)
{
	//GEngine->AddOnScreenDebugMessage(-1, .3f, FColor::Cyan, TEXT("Chase State entered"));
	GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Blue, TEXT("Chase state entered!"));
	//FSM->MoveToPlayer();
	if (!Player)
	{
		Player = FSM->GetPlayer();
	}
	FSM->MoveToActor(Player);
}
