// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy/StruwwelController.h"
#include "Enemy/Struwwel.h"
#include "Enemy/BaseState.h"
#include "Enemy/ChaseState.h"
#include "Enemy/IdleState.h"
#include "Enemy/SearchState.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Sight.h"
#include "Player/PlayerCharacter.h"
#include "NavigationSystem.h"
#include "Animation/AnimSequence.h"
#include "Player/TestCharacter.h"

//TODO: Forget player and enter Search state needs to be implemented
AStruwwelController::AStruwwelController()
{
	//auto aiSystem = GetWorld()->GetSubsystem<UAISubsystem>();
	//GET_AI_CONFIG_VAR(bForgetStaleActors = true);
	//if (GetWorld())
	//{
	//	UAISystem* PerceptionSystem = UAISystem::GetCurrent(GetOwner()->GetWorld());

	//	

	//	
	//	//GetWorld()->GetSubsystem<UAISystem>()->bForgetStaleActors = false;
	//}

	Walk = ConstructorHelpers::FObjectFinder<UAnimSequence>(*WalkAnimPath).Object;

	PerceptionComponent = CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("AI Perception"));
	UAISenseConfig_Sight* SightConfig = CreateDefaultSubobject<UAISenseConfig_Sight>(TEXT("Sight"));
	SightConfig->SightRadius = 1000.f;
	SightConfig->LoseSightRadius = 500.f;
	SightConfig->PeripheralVisionAngleDegrees = 30.f;
	SightConfig->AutoSuccessRangeFromLastSeenLocation = -1;
	SightConfig->DetectionByAffiliation.bDetectEnemies = true;
	SightConfig->DetectionByAffiliation.bDetectFriendlies = true;
	SightConfig->DetectionByAffiliation.bDetectNeutrals = true;
	SightConfig->SetMaxAge(3.f);
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
	case EStates::ST_IDLE:
		CurrentState = EStates::ST_IDLE;
		ActiveState = Idle;
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

	ActiveState->EnterState();
}

void AStruwwelController::UpdateState(float deltaTime)
{
	ActiveState->UpdateState(deltaTime);
}

void AStruwwelController::MoveToPlayer(void)
{
	EPathFollowingRequestResult::Type result = MoveToActor(Player);
	if (result == 0) GEngine->AddOnScreenDebugMessage(-1, .5f, FColor::Red, TEXT("Request failed"));
	else GEngine->AddOnScreenDebugMessage(-1, .5f, FColor::Green, TEXT("Request succeded"));
}

void AStruwwelController::PlayAnimation(void)
{
	Struwwel->GetMesh()->PlayAnimation(Walk, true);
}

void AStruwwelController::BeginPlay()
{
	Super::BeginPlay();
	auto controlledActor = GetPawn();
	Struwwel = Cast<AStruwwel>(controlledActor);
	//if (controlledActor) UE_LOG(LogTemp, Warning, TEXT("Controller is possessing: %s"), *controlledActor->GetName());
}

void AStruwwelController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	UpdateState(DeltaTime);
}

void AStruwwelController::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
	Idle->ConditionalBeginDestroy();
	Chase->ConditionalBeginDestroy();
	Search->ConditionalBeginDestroy();

	Idle = nullptr;
	Chase = nullptr;
	Search = nullptr;


	PerceptionComponent->OnTargetPerceptionForgotten.RemoveDynamic(this, &AStruwwelController::OnPlayerLost);
	PerceptionComponent->OnTargetPerceptionUpdated.RemoveDynamic(this, &AStruwwelController::OnPlayerDetected);
}

void AStruwwelController::OnPlayerDetected(AActor* other, FAIStimulus stimulus)
{
	if (other->IsA( ATestCharacter::StaticClass()))
	{
		GEngine->AddOnScreenDebugMessage(-1, .5f, FColor::Red, TEXT("Player detected"));
		Player = Cast<APlayerCharacter>(other);
		SetState(EStates::ST_CHASE);
		
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

	Idle = NewObject<UIdleState>();
	Idle->SetFSM(this);
	Chase = NewObject<UChaseState>();
	Chase->SetFSM(this);
	Search = NewObject<USearchState>();
	Search->SetFSM(this);
}
