// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/PlayerCharacter.h"
#include "Managers/GameManager.h"
#include "EnhancedInputComponent.h"
#include "InputMappingContext.h"
#include "InputAction.h"
#include <EnhancedInputSubsystems.h>
#include "Utility/ActorUtility.h"
#include "Managers/UIManager.h"
#include "Engine/TriggerBox.h"
#include "Components/CapsuleComponent.h"

// Sets default values
APlayerCharacter::APlayerCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Instantiate();
}

// Called when the game starts or when spawned
void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
	Manager = UGameManager::Instantiate(*this);
	if (Manager) Manager->SetPlayer(this);
	if (auto PlayerController = Cast<APlayerController>(GetController()))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(ContextMapping, 0);
		}
	}
	GetCapsuleComponent()->OnComponentBeginOverlap.AddDynamic(this, &APlayerCharacter::OverlapBegin);
	GetCapsuleComponent()->OnComponentEndOverlap.AddDynamic(this, &APlayerCharacter::OverlapEnd);
}

void APlayerCharacter::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
	GetCapsuleComponent()->OnComponentBeginOverlap.RemoveDynamic(this, &APlayerCharacter::OverlapBegin);
	GetCapsuleComponent()->OnComponentEndOverlap.RemoveDynamic(this, &APlayerCharacter::OverlapEnd);
}


// Called to bind functionality to input
void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	Input = Cast<UEnhancedInputComponent>(PlayerInputComponent);
	Input->BindAction(MoveAction, ETriggerEvent::Triggered, this, &APlayerCharacter::HandleMovement);
	Input->BindAction(MoveAction, ETriggerEvent::Completed, this, &APlayerCharacter::HandleMovement);
	Input->BindAction(JumpAction, ETriggerEvent::Triggered, this, &APlayerCharacter::HandleJump);
	Input->BindAction(PauseAction, ETriggerEvent::Triggered, this, &APlayerCharacter::HandlePause);
}

void APlayerCharacter::OverlapBegin(UPrimitiveComponent* Overlap, AActor* Other, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (Other->IsA(ATriggerBox::StaticClass()))
	{
		GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Red, TEXT("Transition"));

		OnTriggerOverlap.Broadcast();

		UE_LOG(LogTemp, Warning, TEXT("%s"), (OnTriggerOverlap.IsBound() ? TEXT("true") : TEXT("false")));
	}
}

void APlayerCharacter::OverlapEnd(UPrimitiveComponent* Overlap, AActor* Other, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
}

void APlayerCharacter::Instantiate(void)
{
	MoveAction = FindObject<UInputAction>(MoveActionPath);
	JumpAction = FindObject<UInputAction>(JumpActionPath);
	PauseAction = FindObject<UInputAction>(PauseActionPath);
	ContextMapping = FindObject<UInputMappingContext>(ContextPath);
}

void APlayerCharacter::MovePlayer(float DeltaTime)
{
	AddMovementInput(FVector(Direction.X * Speed * DeltaTime, Direction.Y * Speed * DeltaTime, 0));

}

void APlayerCharacter::HandleMovement(const FInputActionValue& Value)
{
	Direction = Value.Get<FVector2D>();
	MovePlayer(GetWorld()->GetDeltaSeconds());
}

void APlayerCharacter::HandleJump(const FInputActionValue& Value)
{
	Jump();
}

void APlayerCharacter::HandlePause(const FInputActionValue& Value)
{
	OnPause.Broadcast();
	Manager->GetUIManager()->PauseGame(this, Value.Get<bool>());
}

