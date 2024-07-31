// Fill out your copyright notice in the Description page of Project Settings.


#include "GameWorld/EnemyTrigger.h"
#include "Components/BoxComponent.h"
#include "Player/TestCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "Enemy/Struwwel.h"

// Sets default values
AEnemyTrigger::AEnemyTrigger()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	Box = CreateDefaultSubobject<UBoxComponent>(TEXT("EnemyTrigger"));


}

// Called when the game starts or when spawned
void AEnemyTrigger::BeginPlay()
{
	Super::BeginPlay();
	auto enemy = UGameplayStatics::GetActorOfClass(GetWorld(), AStruwwel::StaticClass());
	Struwwel = Cast<AStruwwel>(enemy);
	Box->OnComponentBeginOverlap.AddUniqueDynamic(this, &AEnemyTrigger::OverlapBegin);
}

void AEnemyTrigger::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Box->OnComponentBeginOverlap.RemoveDynamic(this, &AEnemyTrigger::OverlapBegin);
}

void AEnemyTrigger::OverlapBegin(UPrimitiveComponent* Overlap, AActor* Other, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (Other->IsA(ATestCharacter::StaticClass()))
	{
		auto player = Cast<ATestCharacter>(Other);
		Struwwel->Instantiate(player);
	}
}


