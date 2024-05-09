// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy/AIComponent.h"
#include "Enemy/EnemyFSM.h"


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
	EnemyFSM = NewObject<UEnemyFSM>();
	// ...
	
}


// Called every frame
void UAIComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

