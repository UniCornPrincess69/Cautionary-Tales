// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy/Struwwel.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Sight.h"
#include "Player/PlayerCharacter.h"
#include "Managers/GameManager.h"
#include "Enemy/StruwwelController.h"


// Sets default values
AStruwwel::AStruwwel()
{

	//TODO: Implement Target forgotten, change to idle/search!
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//EnemyAI = CreateDefaultSubobject<UAIComponent>(TEXT("EnemyAI"));
	/*PerceptionComponent = CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("AI Perception"));
	UAISenseConfig_Sight* SightConfig = CreateDefaultSubobject<UAISenseConfig_Sight>(TEXT("Sight"));
	SightConfig->SightRadius = 1500.f;
	SightConfig->LoseSightRadius = 1600.f;
	SightConfig->PeripheralVisionAngleDegrees = 30.f;
	SightConfig->DetectionByAffiliation.bDetectEnemies = true;
	SightConfig->DetectionByAffiliation.bDetectFriendlies = true;
	SightConfig->DetectionByAffiliation.bDetectNeutrals = true;
	PerceptionComponent->ConfigureSense(*SightConfig);
	PerceptionComponent->SetDominantSense(SightConfig->GetSenseImplementation());
	PerceptionComponent->OnTargetPerceptionUpdated.AddDynamic(this, &AStruwwel::PlayerDetected);*/
}

void AStruwwel::Instantiate(void)
{
	AIControllerClass = AStruwwelController::StaticClass();
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
	Controller = Cast<AStruwwelController>(GetController());

	if (Controller)
	{
		Controller->SetState(EStates::ST_IDLE);
	}
}

// Called when the game starts or when spawned
void AStruwwel::BeginPlay()
{
	Super::BeginPlay();

	auto GM = UGameManager::Instantiate(*this);
	GM->SetEnemy(this);
	
	UE_LOG(LogTemp, Warning, TEXT("Controller: %s"), *GetController()->GetName());
}


// Called every frame
void AStruwwel::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AStruwwel::Test()
{

	
}

void AStruwwel::PlayerDetected(AActor* Other, FAIStimulus Stimulus)
{
	//GEngine->AddOnScreenDebugMessage(-1, .5f, FColor::Purple, TEXT("Stimulus"));
	/*if (Other->IsA(APlayerCharacter::StaticClass()))
	{
		OnPlayerDetection.Broadcast();
	}*/
}


