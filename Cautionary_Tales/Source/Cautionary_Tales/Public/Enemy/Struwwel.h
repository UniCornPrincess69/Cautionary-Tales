// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Struwwel.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnPlayerDetection);

UCLASS()
class CAUTIONARY_TALES_API AStruwwel : public ACharacter
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AStruwwel();

	void Instantiate(void);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float deltaTime) override;

	FOnPlayerDetection OnPlayerDetection;

	UFUNCTION(BlueprintCallable)
		void PlayerDetected(AActor* other, struct FAIStimulus stimulus);
private:
	UFUNCTION(CallInEditor)
	void Test();

	class UAIPerceptionComponent* PerceptionComponent = nullptr;
	class AStruwwelController* Controller = nullptr;
	bool IsActive = false;


};
