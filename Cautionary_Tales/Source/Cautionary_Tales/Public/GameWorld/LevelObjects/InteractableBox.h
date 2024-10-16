// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "InteractableBox.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnTriggerActivated);
UCLASS()
class CAUTIONARY_TALES_API AInteractableBox : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AInteractableBox();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	UFUNCTION()
		void OnBeginOverlap(UPrimitiveComponent* Overlap, AActor* Other, UPrimitiveComponent* OtherComp,
			int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
public:
	FOnTriggerActivated OnTriggerActivated;
private:
	class AGame* Game = nullptr;
	class UBoxComponent* Box = nullptr;
};
