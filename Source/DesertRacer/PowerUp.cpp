#include "Kismet/GameplayStatics.h"
#include "PlayerCharacter.h"
#include "PowerUp.h"

APowerUp::APowerUp()
{
	PrimaryActorTick.bCanEverTick = true;

	CapsuleComponent = CreateDefaultSubobject<UCapsuleComponent>(TEXT("CapsuleComponent"));
	SetRootComponent(CapsuleComponent);

	PowerUpSprite = CreateDefaultSubobject<UPaperSpriteComponent>(TEXT("PowerUpSprite"));
	PowerUpSprite->SetupAttachment(RootComponent);
}

void APowerUp::BeginPlay()
{
	Super::BeginPlay();

	CapsuleComponent->OnComponentBeginOverlap.AddDynamic(this, &APowerUp::OverlapBegin);
}

void APowerUp::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	Rotate(DeltaTime);
}

void APowerUp::Rotate(float DeltaTime)
{
	FRotator DeltaRotation = FRotator::ZeroRotator; 
	DeltaRotation.Pitch = DeltaTime * TurnRate;
	AddActorLocalRotation(DeltaRotation, true);
}

void APowerUp::OverlapBegin(
	UPrimitiveComponent* OverlappedComponent,
	AActor* OtherActor,
	UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex,
	bool FromSweep,
	const FHitResult& SweepResult)
{
	APlayerCharacter* Player = Cast<APlayerCharacter>(OtherActor);
	if (Player)
	{
		UE_LOG(LogTemp, Warning, TEXT("I've got the poweeeeerrrr"));
		UGameplayStatics::PlaySound2D(GetWorld(), HitSound);
		Destroy();
	}
}
