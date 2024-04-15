// Fill out your copyright notice in the Description page of Project Settings.


#include "GameWorld/GameModes/MainMenu_Mode.h"
#include "UI/MainMenuUI.h"

AMainMenu_Mode::AMainMenu_Mode()
{
	HUDClass = AMainMenuUI::StaticClass();
}
