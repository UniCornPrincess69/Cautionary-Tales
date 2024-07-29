// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/InGameUI.h"
#include "Blueprint/UserWidget.h"
#include "Managers/GameManager.h"
#include "Player/TestCharacter.h"


AInGameUI::AInGameUI()
{
	auto pauseUI = ConstructorHelpers::FClassFinder<UUserWidget>((TCHAR*)(*PauseHUDPath)).Class;
	auto endUI = ConstructorHelpers::FClassFinder<UUserWidget>((TCHAR*)(*EndHUDPath)).Class;
	auto deathUI = ConstructorHelpers::FClassFinder<UUserWidget>((TCHAR*)(*DeathHUDPath)).Class;

	if (GetWorld())
	{
		Player = GetWorld()->GetFirstPlayerController();
	}
	else return;

	PauseWidget = CreateWidget(Player, pauseUI, TEXT("Pause Menu"));
	EndWidget = CreateWidget(Player, endUI, TEXT("End screen"));
	DeathWidget = CreateWidget(Player, deathUI, TEXT("Death screen"));

	GM = UGameManager::Instantiate(*this);
	if (GM)
	{
		GM->SetInGameUI(this);
		GM->OnPlayerReady.AddUniqueDynamic(this, &AInGameUI::SetupCallback);
	}


	if (PauseWidget && EndWidget)
	{
		PauseWidget->AddToViewport();
		EndWidget->AddToViewport();
		DeathWidget->AddToViewport();
		InitWidgets();
	}
}

void AInGameUI::InitWidgets(void)
{
	PauseWidget->SetVisibility(ESlateVisibility::Hidden);
	EndWidget->SetVisibility(ESlateVisibility::Hidden);
	DeathWidget->SetVisibility(ESlateVisibility::Hidden);

	if (Player)
	{
		Player->SetShowMouseCursor(false);
		Player->SetInputMode(Game);
	}
}

void AInGameUI::SetPauseWidget(void)
{
	PauseWidget->SetVisibility(ESlateVisibility::Visible);

	if (Player)
	{
		Player->SetShowMouseCursor(true);
		Player->SetInputMode(Both);
	}
}

void AInGameUI::SetEndWidget(void)
{
	EndWidget->SetVisibility(ESlateVisibility::Visible);

	if (Player)
	{
		Player->SetShowMouseCursor(true);
		Player->SetInputMode(Both);
	}
}

void AInGameUI::SetDeathScreen()
{
	DeathWidget->SetVisibility(ESlateVisibility::Visible);
	if (Player)
	{
		Player->SetShowMouseCursor(true);
		Player->SetInputMode(Both);
	}
}

void AInGameUI::SetupCallback(ATestCharacter* character)
{
	Character = character;
	Character->OnGotCaught.AddUniqueDynamic(this, &AInGameUI::SetDeathScreen);
}

void AInGameUI::EndPlay(const EEndPlayReason::Type endPlayReason)
{
	if (GM) GM->OnPlayerReady.RemoveDynamic(this, &AInGameUI::SetupCallback);
	if (Character) Character->OnGotCaught.RemoveDynamic(this, &AInGameUI::SetDeathScreen);
}
