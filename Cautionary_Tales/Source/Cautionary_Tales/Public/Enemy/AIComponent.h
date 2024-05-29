// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "AIComponent.generated.h"

class APlayerCharacter;
class AStruwwelController;
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class CAUTIONARY_TALES_API UAIComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UAIComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type endPlayReason);

private:

	UFUNCTION()
		void PlayerDetected();

	UFUNCTION()
		void PlayerReady(APlayerCharacter* player);

public:	
	// Called every frame
	virtual void TickComponent(float deltaTime, ELevelTick tickType, FActorComponentTickFunction* thisTickFunction) override;

private:
	class UGameManager* Manager = nullptr;
	UPROPERTY(EditAnywhere, meta = (DisplayName = "AI Component", Category = "AI Component"))
	class UEnemyFSM* EnemyFSM = nullptr;
	class AStruwwel* Struwwel = nullptr;
	UPROPERTY(EditAnywhere, meta = (DisplayName = "Target Player", Category = "AI Component"))
	APlayerCharacter* Player = nullptr;
	UPROPERTY(EditAnywhere, meta = (DisplayName = "AI Controller", Category = "AI Component"))
	AStruwwelController* Controller = nullptr;
};
