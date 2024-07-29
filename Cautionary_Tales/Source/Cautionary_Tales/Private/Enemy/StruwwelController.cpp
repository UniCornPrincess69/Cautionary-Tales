// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy/StruwwelController.h"
#include "Enemy/Struwwel.h"
#include "Enemy/BaseState.h"
#include "Enemy/ChaseState.h"
#include "Enemy/AttackState.h"
#include "Enemy/SearchState.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Sight.h"
#include "Player/PlayerCharacter.h"
#include "NavigationSystem.h"
#include "Animation/AnimSequence.h"
#include "Player/TestCharacter.h"
#include "Utility/ActorUtility.h"

AStruwwelController::AStruwwelController()
{
	WalkAnim = FindObject<UAnimSequence>(*WalkAnimPath);
	ChaseAnim = FindObject<UAnimSequence>(*ChaseAnimPath);
	AttackAnim = FindObject<UAnimSequence>(*AttackAnimPath);

	PerceptionComponent = CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("AI Perception"));
	UAISenseConfig_Sight* SightConfig = CreateDefaultSubobject<UAISenseConfig_Sight>(TEXT("Sight"));
	SightConfig->SightRadius = 1000.f;
	SightConfig->LoseSightRadius = 500.f;
	SightConfig->PeripheralVisionAngleDegrees = 35.f;
	SightConfig->DetectionByAffiliation.bDetectEnemies = true;
	SightConfig->DetectionByAffiliation.bDetectFriendlies = true;
	SightConfig->DetectionByAffiliation.bDetectNeutrals = true;
	PerceptionComponent->ConfigureSense(*SightConfig);
	PerceptionComponent->SetDominantSense(SightConfig->GetSenseImplementation());
	PerceptionComponent->OnTargetPerceptionUpdated.AddDynamic(this, &AStruwwelController::OnPlayerDetected);
	PerceptionComponent->OnTargetPerceptionForgotten.AddDynamic(this, &AStruwwelController::OnPlayerLost);
	NavSys = UNavigationSystemV1::GetCurrent(GetWorld());
	
}

void AStruwwelController::SetState(EStates state)
{
	if (CurrentState == state) return;
	if (ActiveState) ActiveState->ExitState();
	switch (state)
	{
	case EStates::ST_ATTACK:
		CurrentState = EStates::ST_ATTACK;
		ActiveState = Attack;
		break;
	case EStates::ST_CHASE:
		CurrentState = EStates::ST_CHASE;
		ActiveState = Chase;
		break;
	case EStates::ST_SEARCH:
		CurrentState = EStates::ST_SEARCH;
		ActiveState = Search;
		break;
	default:
		break;
	}
	Struwwel->SetCurrentState(CurrentState);
	ActiveState->EnterState();
}

void AStruwwelController::UpdateState(float deltaTime)
{
	ActiveState->UpdateState(deltaTime);
}

void AStruwwelController::MoveToPlayer(void)
{
	EPathFollowingRequestResult::Type result = MoveToActor(Player);
	if (result == 0) UE_LOG(LogTemp, Warning, TEXT("Request failed"))
	else UE_LOG(LogTemp, Warning, TEXT("Request succeded"));
}

void AStruwwelController::PlayAnimation(void)
{
	switch (CurrentState)
	{
	case EStates::ST_NONE:
		break;
	case EStates::ST_ATTACK:
		Struwwel->GetMesh()->PlayAnimation(AttackAnim, false);
		break;
	case EStates::ST_CHASE:
		Struwwel->GetMesh()->PlayAnimation(ChaseAnim, true);
		break;
	case EStates::ST_SEARCH:
		Struwwel->GetMesh()->PlayAnimation(WalkAnim, true);
		break;
	default:
		break;
	}
}

void AStruwwelController::BeginPlay()
{
	Super::BeginPlay();
	/*auto controlledActor = GetPawn();
	Struwwel = Cast<AStruwwel>(controlledActor);*/
	//if (controlledActor) UE_LOG(LogTemp, Warning, TEXT("Controller is possessing: %s"), *controlledActor->GetName());
}

void AStruwwelController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if(IsActive) UpdateState(DeltaTime);
}

void AStruwwelController::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
	Attack->ConditionalBeginDestroy();
	Chase->ConditionalBeginDestroy();
	Search->ConditionalBeginDestroy();

	Attack = nullptr;
	Chase = nullptr;
	Search = nullptr;

	PerceptionComponent->OnTargetPerceptionForgotten.RemoveDynamic(this, &AStruwwelController::OnPlayerLost);
	PerceptionComponent->OnTargetPerceptionUpdated.RemoveDynamic(this, &AStruwwelController::OnPlayerDetected);
}

void AStruwwelController::OnPlayerDetected(AActor* other, FAIStimulus stimulus)
{
	if (other->IsA( ATestCharacter::StaticClass()))
	{
		Player = Cast<ATestCharacter>(other);
		SetState(EStates::ST_CHASE);
		Struwwel->SetPlayer(Player);
	}
}

void AStruwwelController::OnPlayerLost(AActor* other)
{
	GEngine->AddOnScreenDebugMessage(-1, .5f, FColor::Blue, TEXT("Player lost"));
	LastPlayerLocation = other->GetActorLocation();
	SetState(EStates::ST_SEARCH);
}

void AStruwwelController::OnPossess(APawn* pawn)
{
	Super::OnPossess(pawn);

	auto controlledActor = GetPawn();
	Struwwel = Cast<AStruwwel>(controlledActor);

	Attack = NewObject<UAttackState>();
	Attack->SetFSM(this);
	Attack->SetWorld(GetWorld());
	Chase = NewObject<UChaseState>();
	Chase->SetFSM(this);
	Search = NewObject<USearchState>();
	Search->SetFSM(this);
}
