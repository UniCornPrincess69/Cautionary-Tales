// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/InGameUI.h"
#include "Blueprint/UserWidget.h"
#include "Managers/GameManager.h"


AInGameUI::AInGameUI()
{
	auto pauseUI = ConstructorHelpers::FClassFinder<UUserWidget>((TCHAR*)(*PauseHUDPath)).Class;
	auto endUI = ConstructorHelpers::FClassFinder<UUserWidget>((TCHAR*)(*EndHUDPath)).Class;

	if (GetWorld())
	{
		Player = GetWorld()->GetFirstPlayerController();
	}
	else return;

	PauseWidget = CreateWidget(Player, pauseUI, TEXT("Pause Menu"));
	EndWidget = CreateWidget(Player, endUI, TEXT("Death screen"));

	auto GM = UGameManager::Instantiate(*this);
	if (GM) GM->SetInGameUI(this);

	if (PauseWidget && EndWidget)
	{
		PauseWidget->AddToViewport();
		EndWidget->AddToViewport();
		InitWidgets();
	}

}

void AInGameUI::InitWidgets(void)
{
	PauseWidget->SetVisibility(ESlateVisibility::Hidden);
	EndWidget->SetVisibility(ESlateVisibility::Hidden);

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
	PauseWidget->SetVisibility(ESlateVisibility::Visible);

	if (Player)
	{
		Player->SetShowMouseCursor(true);
		Player->SetInputMode(Both);
	}
}
