// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/PlayerCharacter.h"
#include "Managers/GameManager.h"
#include "EnhancedInputComponent.h"
#include "InputMappingContext.h"
#include "InputAction.h"
#include <EnhancedInputSubsystems.h>
#include "Utility/ActorUtility.h"

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
	auto GM = UGameManager::Instantiate(*this);
	if (GM) GM->SetPlayer(this);

	UE_LOG(LogTemp, Warning, TEXT("Begin Play"));
	if (APlayerController* PlayerController = Cast<APlayerController>(GetController()))
	{
		UE_LOG(LogTemp, Warning, TEXT("Player Controller"));
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(ContextMapping, 0);
			UE_LOG(LogTemp, Warning, TEXT("Enhanced input"));
		}
	}
}

// Called every frame
void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	MovePlayer(DeltaTime);
}

// Called to bind functionality to input
void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	Input = Cast<UEnhancedInputComponent>(PlayerInputComponent);
	Input->BindAction(MoveAction, ETriggerEvent::Triggered, this, &APlayerCharacter::HandleMovement);
	Input->BindAction(MoveAction, ETriggerEvent::Completed, this, &APlayerCharacter::HandleMovement);
	UE_LOG(LogTemp, Warning, TEXT("Player Input set"));
}

void APlayerCharacter::Instantiate(void)
{
	MoveAction = FindObject<UInputAction>(MoveActionPath);
	ContextMapping = FindObject<UInputMappingContext>(ContextPath);
}

void APlayerCharacter::MovePlayer(float DeltaTime)
{
	auto location = GetActorLocation();
	location += FVector(Direction.X * Speed * DeltaTime, Direction.Y * Speed * DeltaTime, 0);
	SetActorLocation(location);

	GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Orange, FString::Printf(TEXT("X: %f, Y: %f"), Direction.X, Direction.Y));
}

void APlayerCharacter::HandleMovement(const FInputActionValue& Value)
{
	Direction = Value.Get<FVector2D>();
}

