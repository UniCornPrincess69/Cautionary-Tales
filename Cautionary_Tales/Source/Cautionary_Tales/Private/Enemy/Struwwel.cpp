// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy/Struwwel.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Sight.h"
#include "Player/PlayerCharacter.h"
#include "Managers/GameManager.h"
#include "Enemy/StruwwelController.h"
#include "GameFramework/CharacterMovementComponent.h"


// Sets default values
AStruwwel::AStruwwel()
{
	PrimaryActorTick.bCanEverTick = false;

}

void AStruwwel::Instantiate(void)
{
	AIControllerClass = AStruwwelController::StaticClass();
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
	Controller = Cast<AStruwwelController>(GetController());
	bUseControllerRotationYaw = true;
	GetCharacterMovement()->MaxWalkSpeed = 300.f;

	if (Controller)
	{
		Controller->SetState(EStates::ST_SEARCH);
	}
}

// Called when the game starts or when spawned
void AStruwwel::BeginPlay()
{
	Super::BeginPlay();

	auto GM = UGameManager::Instantiate(*this);
	GM->SetEnemy(this);
}


// Called every frame
void AStruwwel::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AStruwwel::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
}

void AStruwwel::StateChanged(EStates newState)
{
	CurrentState = newState;
}




