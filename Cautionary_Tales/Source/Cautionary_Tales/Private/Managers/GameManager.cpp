// Fill out your copyright notice in the Description page of Project Settings.


#include "Managers/GameManager.h"
#include <Runtime/Engine/Classes/Kismet/GameplayStatics.h>
#include "Managers/UIManager.h"
#include "Player/PlayerCharacter.h"

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
	Player = player;
	OnPlayerReady.Broadcast(Player);
}

UUIManager* UGameManager::GetUIManager(void)
{
	auto ui = GetWorld()->GetSubsystem<UUIManager>();
	return ui;
}

void UGameManager::Initialize(FSubsystemCollectionBase& collection)
{
	Super::Initialize(collection);
	UE_LOG(LogTemp, Warning, TEXT("GameManager instantiated"));
}

void UGameManager::Deinitialize()
{
	Super::Deinitialize();
	UE_LOG(LogTemp, Warning, TEXT("GameManager deinstantiated"));
}
