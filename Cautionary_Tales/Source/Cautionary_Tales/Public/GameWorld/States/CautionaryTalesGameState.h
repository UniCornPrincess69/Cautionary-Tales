// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "CautionaryTalesGameState.generated.h"

UENUM()
enum class EGameState
{
	GS_NONE,
	GS_PLAYING,
	GS_PAUSED
};


DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnStateChange, EGameState, ChangedState);
UCLASS()
class CAUTIONARY_TALES_API ACautionaryTalesGameState : public AGameStateBase
{
	GENERATED_BODY()
	
public:
	void SetState(EGameState state);
	FOnStateChange OnStateChange;
private:
	EGameState CurrentState = EGameState::GS_NONE;
};
