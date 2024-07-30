// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/TestCharacter.h"
#include "Engine/LocalPlayer.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/Controller.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"
#include "Engine/TriggerBox.h"
#include "Utility/ActorUtility.h"
#include "Managers/GameManager.h"
#include "Managers/UIManager.h"
#include "Animation/AnimSequence.h"
#include "GameWorld/States/CautionaryTalesGameState.h"
#include "Kismet/GameplayStatics.h"
#include "Enemy/Struwwel.h"


//////////////////////////////////////////////////////////////////////////
// AMyProjectCharacter

/// <summary>
/// Player constructor mostly according to Unreal Character of the Third Person Template
/// </summary>
ATestCharacter::ATestCharacter()
{
	Instantiate();

	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input...	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f); // ...at this rotation rate

	// Note: For faster iteration times these variables, and many more, can be tweaked in the Character Blueprint
	// instead of recompiling to adjust them
	GetCharacterMovement()->JumpZVelocity = 700.f;
	GetCharacterMovement()->AirControl = 0.35f;
	GetCharacterMovement()->MaxWalkSpeed = 500.f;
	GetCharacterMovement()->MinAnalogWalkSpeed = 20.f;
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;
	GetCharacterMovement()->BrakingDecelerationFalling = 1500.0f;

	// Create a camera boom (pulls in towards the player if there is a collision)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 500.0f; // The camera follows at this distance behind the character	
	CameraBoom->bUsePawnControlRotation = true; // Rotate the arm based on the controller


	// Create a follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	FollowCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

	// Note: The skeletal mesh and anim blueprint references on the Mesh component (inherited from Character) 
	// are set in the derived blueprint asset named ThirdPersonCharacter (to avoid direct content references in C++)
}

void ATestCharacter::BeginPlay()
{
	// Call the base class  
	Super::BeginPlay();

	//Add Input Mapping Context
	Manager = UGameManager::Instantiate(*this);
	if (Manager) Manager->SetPlayer(this);
	if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
	}
	if (!CurrentAnim) CurrentAnim = Idle;

	auto gameState = GetWorld()->GetGameState();
	GameState = Cast<ACautionaryTalesGameState>(gameState);

	GetCapsuleComponent()->OnComponentBeginOverlap.AddDynamic(this, &ATestCharacter::OverlapBegin);
	GetCapsuleComponent()->OnComponentEndOverlap.AddDynamic(this, &ATestCharacter::OverlapEnd);
	GetMesh()->PlayAnimation(CurrentAnim, true);

}

void ATestCharacter::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	GetCapsuleComponent()->OnComponentBeginOverlap.RemoveDynamic(this, &ATestCharacter::OverlapBegin);
	GetCapsuleComponent()->OnComponentEndOverlap.RemoveDynamic(this, &ATestCharacter::OverlapEnd);
	GetWorld()->GetTimerManager().ClearTimer(TimerHandle);
	GetMesh()->Stop();
}

void ATestCharacter::OverlapBegin(UPrimitiveComponent* Overlap, AActor* Other, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	GEngine->AddOnScreenDebugMessage(-1, 0.5f, FColor::Emerald, TEXT("Overlap"));


	if (Other->IsA(ATriggerBox::StaticClass()))
	{
		OnTriggerOverlap.Broadcast();
		GEngine->AddOnScreenDebugMessage(-1, 0.5f, FColor::Emerald, TEXT("Transition"));
	}
}

void ATestCharacter::OverlapEnd(UPrimitiveComponent* Overlap, AActor* Other, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
}

/// <summary>
/// Instantiation of all needed objects. Animationsequences, InputActions, InputMappingContext
/// </summary>
/// <param name=""></param>
void ATestCharacter::Instantiate(void)
{
	MoveAction = FindObject<UInputAction>(MoveActionPath);
	JumpAction = FindObject<UInputAction>(JumpActionPath);
	PauseAction = FindObject<UInputAction>(PauseActionPath);
	DefaultMappingContext = FindObject<UInputMappingContext>(ContextPath);
	Crouch = FindObject<UAnimSequence>(CrouchAnimPath);
	Idle = FindObject<UAnimSequence>(IdleAnimPath);
	Walk = FindObject<UAnimSequence>(WalkAnimPath);
}

/// <summary>
/// Function called when Player is in attack range of enemy,
/// prevents Player from moving. Results in Death!
/// </summary>
void ATestCharacter::Caught()
{
	bIsWalking = false;
	CurrentAnim = Crouch;
	GetMesh()->PlayAnimation(CurrentAnim, false);
	bCanMove = false;
	GetWorld()->GetTimerManager().SetTimer(TimerHandle, [this]() {OnGotCaught.Broadcast(); }, 2.f, false);
}

/// <summary>
/// Input setup according to Unreal
/// </summary>
/// <param name="PlayerInputComponent"></param>
void ATestCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent)) {

		// Jumping
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &ACharacter::Jump);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);

		// Moving
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ATestCharacter::Move);
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Completed, this, &ATestCharacter::StopMoving);

		EnhancedInputComponent->BindAction(PauseAction, ETriggerEvent::Triggered, this, &ATestCharacter::Pause);

		// Looking
		//EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &ATestCharacter::Look);
	}
	else
	{
	}
}

/// <summary>
/// Function for the player movement
/// </summary>
/// <param name="Value">Input value from keyboard or gamepad</param>
void ATestCharacter::Move(const FInputActionValue& Value)
{
	if (bCanMove)
	{

		// input is a Vector2D
		FVector2D MovementVector = Value.Get<FVector2D>();

		if (MovementVector >= MinThreshold && MovementVector <= MaxThreshold)
		{
			CurrentAnim = Idle;
			GetMesh()->PlayAnimation(CurrentAnim, true);
			bIsWalking = false;
		}
		else
		{
			// find out which way is forward
			CurrentAnim = Walk;
			if (!bIsWalking)
			{
				GetMesh()->PlayAnimation(CurrentAnim, true);
				bIsWalking = true;
			}

			const FRotator Rotation = Controller->GetControlRotation();
			const FRotator YawRotation(0, Rotation.Yaw, 0);

			// get forward vector
			const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

			// get right vector 
			const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);

			// add movement 
			AddMovementInput(ForwardDirection, MovementVector.Y);
			AddMovementInput(RightDirection, MovementVector.X);
		}
	}

}

/// <summary>
/// Function to stop the movement of the player and change the animation
/// </summary>
/// <param name="Value">Input value from keyboard or gamepad</param>
void ATestCharacter::StopMoving(const FInputActionValue& Value)
{
	bIsWalking = false;
	CurrentAnim = Idle;
	GetMesh()->PlayAnimation(CurrentAnim, true);
}

/// <summary>
/// Pause function to pause the game and open the pause screen
/// </summary>
/// <param name="Value">Input value from keyboard or gamepad</param>
void ATestCharacter::Pause(const FInputActionValue& Value)
{
	OnPause.Broadcast();
	GameState->SetState(EGameState::GS_PAUSED);
	Manager->GetUIManager()->PauseGame(this, Value.Get<bool>());
}

