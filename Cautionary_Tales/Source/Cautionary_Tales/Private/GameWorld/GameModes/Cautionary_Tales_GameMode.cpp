// Fill out your copyright notice in the Description page of Project Settings.


#include "GameWorld/GameModes/Cautionary_Tales_GameMode.h"
#include "Player/TestCharacter.h"
#include "UI/InGameUI.h"
#include "GameWorld/States/CautionaryTalesGameState.h"

ACautionary_Tales_GameMode::ACautionary_Tales_GameMode()
{
	auto PlayerCharacter = ConstructorHelpers::FClassFinder<APawn> (TEXT("/Game/Assets/Blueprints/Character/testcharacter"));
	//static auto charObj = ConstructorHelpers::FClassFinder<APawn>(TEXT("/Script/Engine.Blueprint'/Game/Assets/Blueprints/Character/BP_TestCharacter.BP_TestCharacter'"));

	//DefaultPawnClass = APlayerCharacter::StaticClass();

	//auto player = GetWorld()->SpawnActor<APlayerCharacter>(ACharacter, FVector(0.f, 0.f, 0.f), FRotator(0.f, 0.f, 0.f));

	if (PlayerCharacter.Class != NULL)
	{
		DefaultPawnClass = PlayerCharacter.Class;
		HUDClass = AInGameUI::StaticClass();
		GameStateClass = ACautionaryTalesGameState::StaticClass();

	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("asd"));
	}
}
