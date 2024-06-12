// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "TestCharacter.generated.h"

class USpringArmComponent;
class UCameraComponent;
class UInputMappingContext;
class UInputAction;
struct FInputActionValue;
class UAnimSequence;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnPause);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnTriggerOverlap);

//TODO: Rename this character, save player character just in case. Implement threshold again for controllers
UCLASS()
class ATestCharacter : public ACharacter
{
	GENERATED_BODY()


	/** Look Input Action */

public:
	ATestCharacter();


protected:

	/** Called for movement input */
	void Move(const FInputActionValue& Value);

	/** Called for looking input */
	void Look(const FInputActionValue& Value);

	void Pause(const FInputActionValue& Value);

protected:
	// APawn interface
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// To add mapping context
	virtual void BeginPlay();

	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason);

public:
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	/** Returns FollowCamera subobject **/
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }

	UPROPERTY(BlueprintAssignable)
	FOnPause OnPause;
	FOnTriggerOverlap OnTriggerOverlap;
private:
	void StopMoving(const FInputActionValue& Value);
	void Instantiate(void);

	UAnimSequence* Walk = nullptr;
	UPROPERTY(EditAnywhere, meta = (DisplayName = "Idle", Category = "Animation"))
	UAnimSequence* Idle = nullptr;
	UAnimSequence* CurrentAnim = nullptr;

	FString WalkAnimPath = FString(TEXT("/Game/Assets/Animation/Main_Character/Walk_Cycle/Main_Character_Walkcycle_Anim"));
	FString IdleAnimPath = FString(TEXT("/Game/Assets/Animation/Main_Character/Idle/idle_Anim"));

	USpringArmComponent* CameraBoom = nullptr;
	UCameraComponent* FollowCamera = nullptr;
	UInputMappingContext* DefaultMappingContext = nullptr;
	UInputAction* JumpAction = nullptr;
	UInputAction* MoveAction = nullptr;
	UInputAction* PauseAction = nullptr;
	class UGameManager* Manager = nullptr;

	bool bIsWalking = false;

	FVector2D MinThreshold = FVector2D(-.2f, -.2f);
	FVector2D MaxThreshold = FVector2D(.2f, .2f);
	FVector2D Direction = FVector2D::ZeroVector;
	UPROPERTY(EditAnywhere, meta = (DisplayName = "Speed", Category = "CharacterMovement"))
		float Speed = 50.f;

	const FString MoveActionPath = FString(TEXT("/Game/Assets/Blueprints/Input/IA_Movement"));
	const FString JumpActionPath = FString(TEXT("/Game/Assets/Blueprints/Input/IA_Jump"));
	const FString PauseActionPath = FString(TEXT("/Game/Assets/Blueprints/Input/IA_Pause"));
	const FString ContextPath = FString(TEXT("/Game/Assets/Blueprints/Input/IMC_PlayerMapping"));
};
