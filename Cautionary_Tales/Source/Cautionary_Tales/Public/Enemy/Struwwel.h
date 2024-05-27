// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Struwwel.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnPlayerDetection);

UCLASS()
class CAUTIONARY_TALES_API AStruwwel : public APawn
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AStruwwel();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	FOnPlayerDetection OnPlayerDetection;

	UFUNCTION(BlueprintCallable)
		void PlayerDetected(AActor* Other, struct FAIStimulus Stimulus);
private:
	UFUNCTION(CallInEditor)
	void Test();


	class UAIComponent* EnemyAI = nullptr;
	class UAIPerceptionComponent* PerceptionComponent = nullptr;
	bool IsActive = false;


};
