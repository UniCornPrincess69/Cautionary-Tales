// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Struwwel.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnPlayerDetection);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnPlayerCaught);

class ATestCharacter;
UCLASS()
class CAUTIONARY_TALES_API AStruwwel : public ACharacter
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AStruwwel();

	void Instantiate(ATestCharacter* player);

	inline void SetCurrentState(EStates state) { CurrentState = state; }
	inline void SetPlayer(ATestCharacter* player) { Player = player; }
	void SetWalkSpeed(float speed);

	inline EStates GetCurrentState(void) { return CurrentState; }

	void PlayerCaught(void);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float deltaTime) override;

	FOnPlayerDetection OnPlayerDetection;
	FOnPlayerCaught OnPlayerCaught;

private:
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	UFUNCTION()
	void StateChanged(EStates newState);

	FTimerHandle TimerHandle;
	class UAIPerceptionComponent* PerceptionComponent = nullptr;
	class AStruwwelController* Controller = nullptr;
	class UGameManager* GM = nullptr;
	ATestCharacter* Player = nullptr;
	bool IsActive = false;
	EStates CurrentState = EStates::ST_NONE;

	float Speed = 300.f;
};
