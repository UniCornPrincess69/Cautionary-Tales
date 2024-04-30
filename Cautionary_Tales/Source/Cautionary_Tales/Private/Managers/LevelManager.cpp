// Fill out your copyright notice in the Description page of Project Settings.


#include "Managers/LevelManager.h"
#include <Runtime/Engine/Classes/Kismet/GameplayStatics.h>

//TODO: Load level and character position via Save system
void ULevelManager::LoadLevel(const FName& LevelName)
{
	auto world = GetWorld();
	if (world) UGameplayStatics::OpenLevel(world, LevelName);
}
