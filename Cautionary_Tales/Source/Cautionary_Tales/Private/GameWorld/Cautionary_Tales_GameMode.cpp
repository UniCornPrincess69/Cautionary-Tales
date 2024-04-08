// Fill out your copyright notice in the Description page of Project Settings.


#include "GameWorld/Cautionary_Tales_GameMode.h"

ACautionary_Tales_GameMode::ACautionary_Tales_GameMode()
{
	static ConstructorHelpers::FClassFinder<APawn> PlayerCharacter(TEXT("/Game/Assets/Blueprints/BP_TestCharacter"));
	if (PlayerCharacter.Class != NULL)
	{
		DefaultPawnClass = PlayerCharacter.Class;
	}
}
