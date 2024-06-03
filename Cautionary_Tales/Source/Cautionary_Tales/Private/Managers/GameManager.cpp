// Fill out your copyright notice in the Description page of Project Settings.


#include "Managers/GameManager.h"
#include <Runtime/Engine/Classes/Kismet/GameplayStatics.h>
#include "Managers/UIManager.h"
#include "Player/PlayerCharacter.h"
#include "Managers/LevelManager.h"
#include "Enemy/Struwwel.h"

auto UGameManager::GetGameInstance(const UObject& target) -> UGameInstance* const
{
	if (target.GetWorld() && target.GetWorld()->GetGameInstance())
	{
		return UGameplayStatics::GetGameInstance(target.GetWorld());
	}
	else if (target.IsA(AActor::StaticClass()))
	{
		if (Cast<AActor>(&target)->GetGameInstance()) return GEngine->GetWorld()->GetGameInstance();
	}
	return nullptr;
}

auto UGameManager::Instantiate(const UObject& target) -> UGameManager* const
{
	auto instance = GetGameInstance(target);
	if (instance) return instance->GetSubsystem<UGameManager>();
	else return nullptr;
}

void UGameManager::SetPlayer(APlayerCharacter* player)
{
	UE_LOG(LogTemp, Warning, TEXT("Manager received Player"));
	Player = player;
	GetWorld()->GetTimerManager().SetTimer(TimerHandle, FTimerDelegate::CreateUObject(this, &UGameManager::DelayedPlayerReadyCallback), 3.f, false);
	
}

void UGameManager::SetEnemy(AStruwwel* struwwel)
{
	Struwwel = struwwel;
	Struwwel->Instantiate();
}

UUIManager* UGameManager::GetUIManager(void)
{
	auto ui = GetWorld()->GetSubsystem<UUIManager>();
	return ui;
}

void UGameManager::Initialize(FSubsystemCollectionBase& collection)
{
	Super::Initialize(collection);
}

void UGameManager::Deinitialize()
{
	Super::Deinitialize();
	GetWorld()->GetTimerManager().ClearTimer(TimerHandle);
}

void UGameManager::DelayedPlayerReadyCallback(void)
{
	OnPlayerReady.Broadcast(Player);
	GetWorld()->GetSubsystem<ULevelManager>()->SetGameManager(this);
}
