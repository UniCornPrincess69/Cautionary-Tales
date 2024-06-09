// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy/SearchState.h"
#include "Enemy/StruwwelController.h"
#include "Enemy/Struwwel.h"
#include "NavigationSystem.h"



void USearchState::EnterState(void)
{
	GEngine->AddOnScreenDebugMessage(-1, .5f, FColor::Black, TEXT("Searching..."));

	if (!NavSys)
	{
		NavSys = FSM->GetNavSystem();
		Struwwel = FSM->GetEnemy();
	}
	FSM->MoveToLocation(FSM->GetLastKnownLocation());
}

void USearchState::UpdateState(float deltaTime)
{
	SearchCooldown += deltaTime;

	if (SearchCooldown >= SearchTime)
	{
		auto location = GetRandomPointInRadius(500.f);
		SearchCooldown = 0.f;

		FSM->MoveToLocation(location);
	}
}

void USearchState::ExitState(void)
{
}

FVector USearchState::GetRandomPointInRadius(float radius)
{
	if (!NavSys)
	{
		GEngine->AddOnScreenDebugMessage(-1, .5f, FColor::Purple, TEXT("NavSys is nullptr"));
		return FVector::ZeroVector;
	}
	
	FNavLocation navLocation;
	bool bSuccess = NavSys->GetRandomPointInNavigableRadius(Struwwel->GetActorLocation(), radius, navLocation);
	return bSuccess ? navLocation.Location : FVector::ZeroVector;
}
