// Fill out your copyright notice in the Description page of Project Settings.


#include "Managers/UIManager.h"
#include <Runtime/Engine/Classes/Kismet/GameplayStatics.h>

void UUIManager::StartGame(const UObject* Target)
{
	auto world = Target->GetWorld();
	if (world) UGameplayStatics::OpenLevel(world, "Level_01", true);
	else GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Red, TEXT("Level not found"));
}

void UUIManager::QuitGame(const UObject* Target)
{
	UKismetSystemLibrary::QuitGame(Target->GetWorld(), Target->GetWorld()->GetFirstPlayerController(), EQuitPreference::Quit, true);
}
