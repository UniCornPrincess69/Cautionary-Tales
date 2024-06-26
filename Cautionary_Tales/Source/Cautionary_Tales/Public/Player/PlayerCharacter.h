// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InputActionValue.h"
#include "GameFramework/Character.h"
#include "PlayerCharacter.generated.h"



//DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnPause);
//DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnTriggerOverlap);

class UInputAction;
class UAnimSequence;
UCLASS()
class CAUTIONARY_TALES_API APlayerCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	APlayerCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

public:	
	// Called every frame
	//virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION()
		void OverlapBegin(UPrimitiveComponent* Overlap, AActor* Other, UPrimitiveComponent* OtherComp,
			int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
		void OverlapEnd(UPrimitiveComponent* Overlap, AActor* Other, UPrimitiveComponent* OtherComp,
			int32 OtherBodyIndex);

	UFUNCTION(Category = "Test Function", CallInEditor)
	void Test();

private:
	void Instantiate(void);
	void MovePlayer(float DeltaTime);
	void HandleMovement(const FInputActionValue& Value);
	void HandleJump(const FInputActionValue& Value);
	void HandlePause(const FInputActionValue& Value);

private:
	class UEnhancedInputComponent* Input = nullptr;
	UInputAction* MoveAction = nullptr;
	UInputAction* JumpAction = nullptr;
	UInputAction* PauseAction = nullptr;
	class UInputMappingContext* ContextMapping = nullptr;
	class UGameManager* Manager = nullptr;

#pragma region Character Setup
	class UCameraComponent* Camera = nullptr;
	class USpringArmComponent* CameraBoom = nullptr;
#pragma endregion

public:
	/*UPROPERTY(BlueprintAssignable)
	FOnPause OnPause;
	FOnTriggerOverlap OnTriggerOverlap;*/
private:

	UAnimSequence* Walk = nullptr;
	UAnimSequence* Idle = nullptr;
	UAnimSequence* CurrentAnim = nullptr;

	FString WalkAnimPath = FString(TEXT("/Game/Assets/Animation/Main_Character/Walk_Cycle/Main_Character_Walkcycle_Anim"));
	FString IdleAnimPath = FString(TEXT("/Game/Assets/Animation/Main_Character/Idle/idle_Anim"));

#pragma region Movement
	FVector2D MinThreshold = FVector2D(-.2f, -.2f);
	FVector2D MaxThreshold = FVector2D(.2f, .2f);
	FVector2D Direction = FVector2D::ZeroVector;
	UPROPERTY(EditAnywhere, meta = (DisplayName = "Speed", Category = "CharacterMovement"))
	float Speed = 50.f;
#pragma endregion

#pragma region Constants
	const FString MoveActionPath = FString(TEXT("/Game/Assets/Blueprints/Input/IA_Movement"));
	const FString JumpActionPath = FString(TEXT("/Game/Assets/Blueprints/Input/IA_Jump"));
	const FString PauseActionPath = FString(TEXT("/Game/Assets/Blueprints/Input/IA_Pause"));
	const FString ContextPath = FString(TEXT("/Game/Assets/Blueprints/Input/IMC_PlayerMapping"));
#pragma endregion

};
