// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/PlayerCharacter.h"
#include "Managers/GameManager.h"
#include "EnhancedInputComponent.h"
#include "InputMappingContext.h"
#include "InputAction.h"
#include <EnhancedInputSubsystems.h>
#include "Utility/ActorUtility.h"
#include "Managers/UIManager.h"

// Sets default values
APlayerCharacter::APlayerCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
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
	UE_LOG(LogTemp, Warning, TEXT("Player Input set"));
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
	//auto location = GetActorLocation();
	//location += FVector(Direction.X * Speed * DeltaTime, Direction.Y * Speed * DeltaTime, 0);
	//SetActorLocation(location);

	AddMovementInput(FVector(Direction.X * Speed * DeltaTime, Direction.Y * Speed * DeltaTime, 0));

}

void APlayerCharacter::HandleMovement(const FInputActionValue& Value)
{
	Direction = Value.Get<FVector2D>();
	//GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Orange, FString::Printf(TEXT("X: %f, Y: %f"), Direction.X, Direction.Y));
	//auto delta = GetWorld()->GetDeltaSeconds();
	MovePlayer(GetWorld()->GetDeltaSeconds());
}

void APlayerCharacter::HandleJump(const FInputActionValue& Value)
{

	Jump();
}

void APlayerCharacter::HandlePause(const FInputActionValue& Value)
{
	GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Blue, FString::Printf(TEXT("Paused")));
	UE_LOG(LogTemp, Warning, TEXT("Pause"));
	
	//Manager->GetUIManager()->PauseGame(this, Value.Get<bool>());

	GetWorld()->GetSubsystem<UUIManager>()->PauseGame(this, Value.Get<bool>());
}

