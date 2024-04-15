// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/MainMenuUI.h"
#include "Blueprint/UserWidget.h"
#include "Utility/ActorUtility.h"

AMainMenuUI::AMainMenuUI()
{
	auto menu = ConstructorHelpers::FClassFinder<UUserWidget>((TCHAR*)(*WidgetPath)).Class;
	APlayerController* player = nullptr;
	if (GetWorld()) player = GetWorld()->GetFirstPlayerController();
	else return;

	MainMenuWidget = CreateWidget(player, menu, "Main Menu");

	SetMainMenu();
}

void AMainMenuUI::SetMainMenu(void)
{
	if (MainMenuWidget)
	{
		MainMenuWidget->AddToViewport();
		auto PC = GetWorld()->GetFirstPlayerController();
		PC->bShowMouseCursor = true;
	}
}
