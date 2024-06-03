// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy/ChaseState.h"
#include "Enemy/EnemyFSM.h"
#include "Player/PlayerCharacter.h"
#include "Enemy/Struwwel.h"
#include "Enemy/StruwwelController.h"



void UChaseState::UpdateState(void)
{

	/*FVector Direction = Player->GetActorLocation() - Struwwel->GetActorLocation();
	Direction.Normalize();
	Struwwel->AddMovementInput(Direction, 1.f);*/
	if (!PlayerInRange()) FSM->SetState(EStates::ST_SEARCH);

}

void UChaseState::ExitState(void)
{
	//GEngine->AddOnScreenDebugMessage(-1, .5f, FColor::Blue, TEXT("Chase exited"));
}

bool UChaseState::PlayerInRange(void)
{
	auto distance = FVector::Distance(Struwwel->GetActorLocation(), Player->GetActorLocation());
	
	if (distance >= 100.f) return false;
	else return true;
}

void UChaseState::EnterState(void)
{
	//GEngine->AddOnScreenDebugMessage(-1, .3f, FColor::Cyan, TEXT("Chase State entered"));
	GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Blue, TEXT("Chase state entered!"));
	FSM->MoveToPlayer();
	if (!Struwwel && !Player)
	{
		Struwwel = FSM->GetEnemy();
		Player = FSM->GetPlayer();
	}
	//FSM->MoveToActor(Player);
}
