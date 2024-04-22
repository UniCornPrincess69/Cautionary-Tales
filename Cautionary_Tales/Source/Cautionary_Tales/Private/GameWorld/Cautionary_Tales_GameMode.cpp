// Fill out your copyright notice in the Description page of Project Settings.


#include "GameWorld/Cautionary_Tales_GameMode.h"
#include "Player/PlayerCharacter.h"
#include "UI/InGameUI.h"

ACautionary_Tales_GameMode::ACautionary_Tales_GameMode()
{
	static ConstructorHelpers::FClassFinder<APawn> PlayerCharacter(TEXT("/Game/Assets/Blueprints/Character/BP_PlayerCharacter"));
	//static auto charObj = ConstructorHelpers::FClassFinder<APawn>(TEXT("/Script/Engine.Blueprint'/Game/Assets/Blueprints/Character/BP_TestCharacter.BP_TestCharacter'"));

	//DefaultPawnClass = APlayerCharacter::StaticClass();

	//auto player = GetWorld()->SpawnActor<APlayerCharacter>(ACharacter, FVector(0.f, 0.f, 0.f), FRotator(0.f, 0.f, 0.f));

	if (PlayerCharacter.Class != NULL)
	{
		DefaultPawnClass = PlayerCharacter.Class;
		HUDClass = AInGameUI::StaticClass();
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("asd"));
	}
}
