// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy/Struwwel.h"
#include "Enemy/AIComponent.h"

// Sets default values
AStruwwel::AStruwwel()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	EnemyAI = CreateDefaultSubobject<UAIComponent>(TEXT("EnemyAI"));
}

// Called when the game starts or when spawned
void AStruwwel::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AStruwwel::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

