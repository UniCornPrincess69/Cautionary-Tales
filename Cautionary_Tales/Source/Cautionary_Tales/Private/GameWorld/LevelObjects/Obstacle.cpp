// Fill out your copyright notice in the Description page of Project Settings.


#include "GameWorld/LevelObjects/Obstacle.h"
#include "Managers/GameManager.h"
#include "Enemy/Struwwel.h"

// Sets default values
AObstacle::AObstacle()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

}

// Called when the game starts or when spawned
void AObstacle::BeginPlay()
{
	Super::BeginPlay();
	
}


