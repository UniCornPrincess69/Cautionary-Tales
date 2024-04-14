// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InputActionValue.h"
#include "GameFramework/Character.h"
#include "PlayerCharacter.generated.h"



class UInputAction;
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

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:
	void Instantiate(void);
	void MovePlayer(float DeltaTime);
	void HandleMovement(const FInputActionValue& Value);
	void HandleJump(const FInputActionValue& Value);

private:
	class UEnhancedInputComponent* Input = nullptr;
	UInputAction* MoveAction = nullptr;
	UInputAction* JumpAction = nullptr;
	UInputAction* PauseAction = nullptr;
	class UInputMappingContext* ContextMapping = nullptr;

#pragma region Movement
	FVector2D Direction = FVector2D::ZeroVector;
	UPROPERTY(EditAnywhere, meta = (DisplayName = "Speed", Category = "CharacterMovement"))
	float Speed = 150.f;
#pragma endregion

#pragma region Constants
	const FString MoveActionPath = FString(TEXT("/Game/Assets/Blueprints/Input/IA_Movement"));
	const FString JumpActionPath = FString(TEXT("/Game/Assets/Blueprints/Input/IA_Jump"));
	const FString ContextPath = FString(TEXT("/Game/Assets/Blueprints/Input/IMC_PlayerMapping"));
#pragma endregion

};
