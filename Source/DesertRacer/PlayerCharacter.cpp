#include "DesertRacerTimer.h"
#include "PlayerCharacter.h"

APlayerCharacter::APlayerCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	CapsuleComponent = CreateDefaultSubobject<UCapsuleComponent>(TEXT("CapsuleComponent"));
	SetRootComponent(CapsuleComponent);

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArm->SetupAttachment(RootComponent);

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm, USpringArmComponent::SocketName);

	CarSprite = CreateDefaultSubobject<UPaperSpriteComponent>(TEXT("CarSprite"));
	CarSprite->SetupAttachment(RootComponent);

}

void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();

	APlayerController *PlayerController = Cast<APlayerController>(Controller);
	if (PlayerController)
	{
		UEnhancedInputLocalPlayerSubsystem *Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer());
		if (Subsystem)
		{
			Subsystem->AddMappingContext(InputMappingContext, 0);
		}

		HUD = CreateWidget(PlayerController, HUDClass);
		if (HUD != nullptr)
		{
			HUD->AddToViewport();
		}
	}
}

void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	UEnhancedInputComponent *EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent);
	if (EnhancedInputComponent)
	{
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &APlayerCharacter::Move);
	}
}

void APlayerCharacter::Move(const FInputActionValue& Value)
{
	FVector2D MoveActionValue = Value.Get<FVector2D>();
	if (CanMove)
	{
		if (abs(MoveActionValue.Y) > 0)
		{
			float DeltaTime = GetWorld()->DeltaTimeSeconds;
			float FinalMovementSpeed = (MoveActionValue.Y < 0) ? MovementSpeed * 0.5 : MovementSpeed;

			if (abs(MoveActionValue.X) > 0)
			{
				// Negative rotation speed gives us "natural" rotation. Otherwise it would be inversed, D would rotate to the left and A to the right
				float Rotation = -RotationSpeed * MoveActionValue.X * DeltaTime;

				// Since it's a 2D game, only the Pitch (Z axis) should be affected by rotation
				AddActorWorldRotation(FRotator(Rotation, 0, 0));
			}

			FVector DistanceToMove = GetActorUpVector() * FinalMovementSpeed * MoveActionValue.Y * DeltaTime;
			FVector NewLocation = GetActorLocation() + DistanceToMove;

			SetActorLocation(NewLocation);
		}
	}
}

void APlayerCharacter::NewHighScore()
{
	UDesertRacerTimer* Timer = Cast<UDesertRacerTimer>(HUD);
	if (Timer)
	{
		Timer->NewHighScoreAnimation();
	}
}
