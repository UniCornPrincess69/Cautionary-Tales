// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "StruwwelController.generated.h"

/**
 *
 */

enum class EStates
{
	ST_NONE,
	ST_IDLE,
	ST_CHASE,
	ST_SEARCH
};

class APlayerCharacter;
class UBaseState;
UCLASS()
class CAUTIONARY_TALES_API AStruwwelController : public AAIController
{
	GENERATED_BODY()

		AStruwwelController();


public:
	void SetState(EStates state);
	void UpdateState(void);

	inline APlayerCharacter* GetPlayer(void) { return Player; }
	inline AStruwwel* GetEnemy(void) { return Struwwel; }

	void MoveToPlayer(void);

private:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason);

	UFUNCTION()
		void OnPlayerDetected(AActor* other, FAIStimulus stimulus);

	UFUNCTION()
		void OnPlayerLost(AActor* other);

	virtual void OnPossess(APawn* pawn) override;

	class AStruwwel* Struwwel = nullptr;


	EStates CurrentState = EStates::ST_NONE;
	UPROPERTY(EditAnywhere, meta = (DisplayName = "Current State", Category = "FSM"))
		UBaseState* ActiveState = nullptr;
	UPROPERTY(EditAnywhere, meta = (DisplayName = "IdleState", Category = "FSM"))
		UBaseState* Idle = nullptr;
	UPROPERTY(EditAnywhere, meta = (DisplayName = "ChaseState", Category = "FSM"))
		UBaseState* Chase = nullptr;
	UPROPERTY(EditAnywhere, meta = (DisplayName = "SearchState", Category = "FSM"))
		UBaseState* Search = nullptr;

	UPROPERTY(EditAnywhere, meta = (DisplayName = "Player", Category = "FSM"))
		APlayerCharacter* Player = nullptr;

	/*UPROPERTY(EditAnywhere, meta = (DisplayName = "Perception", Category = "FSM"))
		UAIPerceptionComponent* PerceptionComponent = nullptr;*/
};
