// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Struwwel.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnPlayerDetection);

UCLASS()
class CAUTIONARY_TALES_API AStruwwel : public ACharacter
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AStruwwel();

	void Instantiate(void);

	inline void SetCurrentState(EStates state) { CurrentState = state; }
	inline EStates GetCurrentState(void) { return CurrentState; }

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float deltaTime) override;

	FOnPlayerDetection OnPlayerDetection;

private:
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	UFUNCTION()
	void StateChanged(EStates newState);


	class UAIPerceptionComponent* PerceptionComponent = nullptr;
	class AStruwwelController* Controller = nullptr;
	bool IsActive = false;
	EStates CurrentState = EStates::ST_NONE;

};
