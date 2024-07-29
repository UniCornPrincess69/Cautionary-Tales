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
class AStruwwel;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnPause);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnTriggerOverlap);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnGotCaught);

//TODO: Rename this character, save player character just in case. Implement threshold again for controllers
UCLASS(BlueprintType)
class ATestCharacter : public ACharacter
{
	GENERATED_BODY()


	/** Look Input Action */

public:
	ATestCharacter();


protected:

	/** Called for movement input */
	void Move(const FInputActionValue& Value);


	void Pause(const FInputActionValue& Value);

protected:
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual void BeginPlay();

	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason);

public:
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }
	UFUNCTION()
	void OverlapBegin(UPrimitiveComponent* Overlap, AActor* Other, UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OverlapEnd(UPrimitiveComponent* Overlap, AActor* Other, UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex);

	inline void SetEnemy(AStruwwel* struwwel) { Struwwel = struwwel; }

	void Caught(void);
private:
	void StopMoving(const FInputActionValue& Value);
	void Instantiate(void);


#pragma region Delegates
public:
	UPROPERTY(BlueprintAssignable)
	FOnPause OnPause;
	FOnTriggerOverlap OnTriggerOverlap;
	FOnGotCaught OnGotCaught;
	FTimerHandle TimerHandle;
#pragma endregion

#pragma region Pointer
private:
	UAnimSequence* Crouch = nullptr;
	UAnimSequence* Walk = nullptr;
	UAnimSequence* Idle = nullptr;
	UAnimSequence* CurrentAnim = nullptr;


	USpringArmComponent* CameraBoom = nullptr;
	UCameraComponent* FollowCamera = nullptr;
	UInputMappingContext* DefaultMappingContext = nullptr;
	UInputAction* JumpAction = nullptr;
	UInputAction* MoveAction = nullptr;
	UInputAction* PauseAction = nullptr;
	class UGameManager* Manager = nullptr;
	class ACautionaryTalesGameState* GameState = nullptr;
	AStruwwel* Struwwel = nullptr;

#pragma endregion
#pragma region Variables
	bool bIsWalking = false;
	bool bCanMove = true;
	FVector2D MinThreshold = FVector2D(-.2f, -.2f);
	FVector2D MaxThreshold = FVector2D(.2f, .2f);
	FVector2D Direction = FVector2D::ZeroVector;
	UPROPERTY(EditAnywhere, meta = (DisplayName = "Speed", Category = "CharacterMovement"))
		float Speed = 50.f;
#pragma endregion
#pragma region Constants
	const FString WalkAnimPath = FString(TEXT("/Game/Assets/Animation/Main_Character/Walk_Cycle/Main_Character_Walkcycle_Anim"));
	const FString CrouchAnimPath = FString(TEXT("/Game/Assets/Animation/Main_Character/Crouch_Cycle/Crouch_Cycle_Anim"));
	const FString IdleAnimPath = FString(TEXT("/Game/Assets/Animation/Main_Character/Idle/idle_Anim"));
	const FString MoveActionPath = FString(TEXT("/Game/Assets/Blueprints/Input/IA_Movement"));
	const FString JumpActionPath = FString(TEXT("/Game/Assets/Blueprints/Input/IA_Jump"));
	const FString PauseActionPath = FString(TEXT("/Game/Assets/Blueprints/Input/IA_Pause"));
	const FString ContextPath = FString(TEXT("/Game/Assets/Blueprints/Input/IMC_PlayerMapping"));
#pragma endregion


};
