// Fill out your copyright notice in the Description page of Project Settings.


#include "GameWorld/LevelScriptActors/LevelScriptActor_Level_01.h"
#include "Enemy/StruwwelController.h"
#include "NavigationSystem.h"

void ALevelScriptActor_Level_01::BeginPlay()
{
	GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Red, TEXT("Level 1 loaded!!"));
	auto navSys = UNavigationSystemV1::GetCurrent(GetWorld());
	navSys->Build();
}
