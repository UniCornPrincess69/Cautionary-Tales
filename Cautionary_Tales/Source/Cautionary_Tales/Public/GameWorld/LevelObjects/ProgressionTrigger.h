// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ProgressionTrigger.generated.h"


UENUM()
enum class ELevels
{
	L_NONE,
	L_ONE,
	L_TWO
};


UCLASS()
class CAUTIONARY_TALES_API AProgressionTrigger : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AProgressionTrigger();

	void Instantiate(ELevels level);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	void LevelOneSetup(void);
	void LevelTwoSetup(void);

	class UBoxComponent* TriggerBox = nullptr;

};
