// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "StruwwelController.generated.h"

/**
 *
 */

UENUM()
enum class EStates
{
	ST_NONE,
	ST_IDLE,
	ST_CHASE,
	ST_SEARCH
};

class ATestCharacter;
class UBaseState;
class UNavigationSystemV1;
class UAnimSequence;
UCLASS()
class CAUTIONARY_TALES_API AStruwwelController : public AAIController
{
	GENERATED_BODY()

		AStruwwelController();


public:
	void SetState(EStates state);
	void UpdateState(float deltaTime);

	inline void SetNavSystem(UNavigationSystemV1* navSys) { NavSys = navSys; }

	inline ATestCharacter* GetPlayer(void) { return Player; }
	inline AStruwwel* GetEnemy(void) { return Struwwel; }
	inline UNavigationSystemV1* GetNavSystem(void) { return NavSys; }
	inline FVector GetLastKnownLocation(void) { return LastPlayerLocation; }

	void MoveToPlayer(void);

	void PlayAnimation(void);

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

	UAnimSequence* Walk = nullptr;

	FString WalkAnimPath = FString(TEXT("/Game/Assets/Animation/Struwelpeter/Walk/Struwelpeter_walk_Anim"));

#pragma region States
private:

	EStates CurrentState = EStates::ST_NONE;
	UPROPERTY(EditAnywhere, meta = (DisplayName = "Current State", Category = "FSM"))
		UBaseState* ActiveState = nullptr;
	UPROPERTY(EditAnywhere, meta = (DisplayName = "IdleState", Category = "FSM"))
		UBaseState* Idle = nullptr;
	UPROPERTY(EditAnywhere, meta = (DisplayName = "ChaseState", Category = "FSM"))
		UBaseState* Chase = nullptr;
	UPROPERTY(EditAnywhere, meta = (DisplayName = "SearchState", Category = "FSM"))
		UBaseState* Search = nullptr;
#pragma endregion

	UPROPERTY(EditAnywhere, meta = (DisplayName = "Player", Category = "FSM"))
		ATestCharacter* Player = nullptr;

	UNavigationSystemV1* NavSys = nullptr;

	FVector LastPlayerLocation;

	/*UPROPERTY(EditAnywhere, meta = (DisplayName = "Perception", Category = "FSM"))
		UAIPerceptionComponent* PerceptionComponent = nullptr;*/
};
