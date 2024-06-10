// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/PlayerCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
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
	/*if (!CurrentAnim) CurrentAnim = Idle;
	GetMesh()->PlayAnimation(CurrentAnim, true);*/
}

void APlayerCharacter::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
	GetCapsuleComponent()->OnComponentBeginOverlap.RemoveDynamic(this, &APlayerCharacter::OverlapBegin);
	GetCapsuleComponent()->OnComponentEndOverlap.RemoveDynamic(this, &APlayerCharacter::OverlapEnd);
	//GetMesh()->Stop();
}


// Called to bind functionality to input
void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	Input = Cast<UEnhancedInputComponent>(PlayerInputComponent);
	Input->BindAction(MoveAction, ETriggerEvent::Triggered, this, &APlayerCharacter::HandleMovement);
	//Input->BindAction(MoveAction, ETriggerEvent::Completed, this, &APlayerCharacter::HandleMovement);
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

void APlayerCharacter::Test()
{
	auto old = GetActorRotation();
	UE_LOG(LogTemp, Warning, TEXT("X: %f, Y: %f, Z: %f"), old.Roll, old.Pitch, old.Yaw);
	SetActorRelativeRotation(FRotator(.0f, 90.f, .0f));
	//SetActorRotation(FRotator(.0f, 90.f, .0f));
	auto orient = GetActorRotation();
	UE_LOG(LogTemp, Warning, TEXT("X: %f, Y: %f, Z: %f"), orient.Roll, orient.Pitch, orient.Yaw);
}

void APlayerCharacter::Instantiate(void)
{
	MoveAction = FindObject<UInputAction>(MoveActionPath);
	JumpAction = FindObject<UInputAction>(JumpActionPath);
	PauseAction = FindObject<UInputAction>(PauseActionPath);
	ContextMapping = FindObject<UInputMappingContext>(ContextPath);
	Walk = FindObject<UAnimSequence>(WalkAnimPath);
	Idle = FindObject<UAnimSequence>(IdleAnimPath);
	//bUseControllerRotationPitch = false;
	//bUseControllerRotationRoll = false;
	//bUseControllerRotationYaw = false;
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->bUseControllerDesiredRotation = false;
	GetCharacterMovement()->RotationRate = FRotator(0.f, 500.f, 0.f);
}

void APlayerCharacter::MovePlayer(float DeltaTime)
{// find out which way is forward
	const FRotator Rotation = Controller->GetControlRotation();
	const FRotator YawRotation(0, Rotation.Yaw, 0);

	// get forward vector
	const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X) * Speed * DeltaTime;

	// get right vector 
	const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y) * Speed * DeltaTime;

	// add movement 
	AddMovementInput(ForwardDirection, Direction.X * Speed * DeltaTime);
	AddMovementInput(RightDirection, Direction.Y * Speed * DeltaTime);
	//AddMovementInput(FVector(Direction.X * Speed * DeltaTime, Direction.Y * Speed * DeltaTime, 0));
	//AddActorLocalRotation(FRotator(0, 90, 0));
	//GetRootComponent()->SetRelativeRotation(FRotator(0.f, 90.f, 0.f)); 

	auto orient = GetActorRotation();
}

void APlayerCharacter::HandleMovement(const FInputActionValue& Value)
{
	FVector2D MovementVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// find out which way is forward
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);

		// get right vector 
		const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

		// add movement 
		AddMovementInput(ForwardDirection, MovementVector.Y);
		AddMovementInput(RightDirection, MovementVector.X);
		UE_LOG(LogTemp, Warning, TEXT("X: %f, Y: %f, Z: %f"), Rotation.Roll, Rotation.Pitch, Rotation.Yaw);
	}





	//auto value = Value.Get<FVector2D>();
	//if (value >= MinThreshold && value <= MaxThreshold)
	//{
	//	/*GetMesh()->Stop();
	//	CurrentAnim = Idle;*/
	//	Direction = FVector2D::ZeroVector;
	//}
	//else
	//{
	//	/*GetMesh()->Stop();
	//	CurrentAnim = Walk;*/
	//	Direction = Value.Get<FVector2D>();
	//}
	//MovePlayer(GetWorld()->GetDeltaSeconds());
	////GetMesh()->PlayAnimation(CurrentAnim, true);
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

