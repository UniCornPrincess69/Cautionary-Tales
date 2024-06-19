// Fill out your copyright notice in the Description page of Project Settings.


#include "GameWorld/LevelScriptActors/Game.h"
#include "Kismet/GameplayStatics.h"

void AGame::BeginPlay()
{
	UGameplayStatics::LoadStreamLevel(this, "Level_01", true, true, FLatentActionInfo());


}
