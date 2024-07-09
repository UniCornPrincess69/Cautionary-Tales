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
		CurrentLocation = Struwwel->GetActorLocation();
	}
	auto loc = FSM->GetLastKnownLocation();
	if (loc == FVector::ZeroVector)
	{
		NextLocation = GetRandomPointInRadius(SearchRadius);
		FSM->MoveToLocation(NextLocation);
	}
	else
	{
		NextLocation = FSM->GetLastKnownLocation();
		FSM->MoveToLocation(NextLocation);
	}
	FSM->PlayAnimation();

}

void USearchState::UpdateState(float deltaTime)
{
	CurrentLocation = Struwwel->GetActorLocation();
	if (FVector::Dist(CurrentLocation, NextLocation) <= Tolerance)
	{
		GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Blue, TEXT("Search updated"));
		CurrentLocation = Struwwel->GetActorLocation();
		NextLocation = GetRandomPointInRadius(SearchRadius);
		FSM->MoveToLocation(NextLocation);
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

bool USearchState::IsAtLocation(FVector TargetLocation)
{
	if (FVector::Dist(CurrentLocation, TargetLocation) <= Tolerance) return true;
	else return false;
}
