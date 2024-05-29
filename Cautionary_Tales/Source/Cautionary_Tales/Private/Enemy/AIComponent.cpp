 // Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy/AIComponent.h"
#include "Enemy/EnemyFSM.h"
#include "Enemy/Struwwel.h"
#include "Player/PlayerCharacter.h"
#include "Managers/GameManager.h"
#include "Enemy/StruwwelController.h"


//TODO: Implementing logic and connecting of everything AI related
// Sets default values for this component's properties
UAIComponent::UAIComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UAIComponent::BeginPlay()
{
	Super::BeginPlay();
	Manager = UGameManager::Instantiate(*this);
	Manager->OnPlayerReady.AddDynamic(this, &UAIComponent::PlayerReady);
	EnemyFSM = NewObject<UEnemyFSM>();
	Struwwel = Cast<AStruwwel>(GetOwner());
	Struwwel->OnPlayerDetection.AddDynamic(this, &UAIComponent::PlayerDetected);
	Controller = Struwwel->GetController<AStruwwelController>();
}

void UAIComponent::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
	Manager->OnPlayerReady.RemoveDynamic(this, &UAIComponent::PlayerReady);
	Struwwel->OnPlayerDetection.RemoveDynamic(this, &UAIComponent::PlayerDetected);
	EnemyFSM = nullptr;
}

void UAIComponent::PlayerDetected()
{
	EnemyFSM->ChangeState(EStates::ST_CHASE);
}

void UAIComponent::PlayerReady(APlayerCharacter* player)
{
	Player = player;
	UE_LOG(LogTemp, Warning, TEXT("Player: %s"), *Player->GetName());
	EnemyFSM->SetPlayer(Player);
	EnemyFSM->SetEnemy(Struwwel);
	EnemyFSM->SetAIController(Controller);
}


// Called every frame
void UAIComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	EnemyFSM->UpdateState();
}

