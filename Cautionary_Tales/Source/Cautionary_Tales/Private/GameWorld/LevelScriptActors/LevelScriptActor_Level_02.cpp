// Fill out your copyright notice in the Description page of Project Settings.


#include "GameWorld/LevelScriptActors/LevelScriptActor_Level_02.h"
#include "Managers/LevelManager.h"

ALevelScriptActor_Level_02::ALevelScriptActor_Level_02()
{
	if (GetWorld())
	{
		auto LM = GetWorld()->GetSubsystem<ULevelManager>();
		if (LM) LM->SetLevelTwo(this);
	}
}

void ALevelScriptActor_Level_02::BeginPlay()
{
	GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Red, TEXT("Level 2 loaded"));
}
