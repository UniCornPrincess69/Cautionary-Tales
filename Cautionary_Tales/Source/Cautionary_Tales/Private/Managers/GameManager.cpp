// Fill out your copyright notice in the Description page of Project Settings.


#include "Managers/GameManager.h"
#include <Runtime/Engine/Classes/Kismet/GameplayStatics.h>
#include "Managers/UIManager.h"

auto UGameManager::GetGameInstance(const UObject& target) -> UGameInstance* const
{
	if (target.GetWorld() && target.GetWorld()->GetGameInstance())
	{
		UGameplayStatics::GetGameInstance(target.GetWorld());
	}
	else if (target.IsA(AActor::StaticClass()))
	{
		if (Cast<AActor>(&target)->GetGameInstance()) return GEngine->GetWorld()->GetGameInstance();
	}
	return nullptr;
}

auto UGameManager::Instantiate(const UObject& target) -> UGameManager* const
{
	auto Instance = GetGameInstance(target);
	if (Instance) return Instance->GetSubsystem<UGameManager>();
	else return nullptr;
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
