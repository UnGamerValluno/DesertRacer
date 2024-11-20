#include "Obstacle.h"
#include "PlayerCharacter.h"

AObstacle::AObstacle()
{
	PrimaryActorTick.bCanEverTick = true;

	CapsuleComponent = CreateDefaultSubobject<UCapsuleComponent>(TEXT("CapsuleComponent"));
	SetRootComponent(CapsuleComponent);

	ObstacleSprite = CreateDefaultSubobject<UPaperSpriteComponent>(TEXT("ObstacleSprite"));
	ObstacleSprite->SetupAttachment(RootComponent);
}

void AObstacle::BeginPlay()
{
	Super::BeginPlay();

	CapsuleComponent->OnComponentBeginOverlap.AddDynamic(this, &AObstacle::OverlapBegin);
}

void AObstacle::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AObstacle::OverlapBegin(
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
		GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::White, TEXT("me'strellao"));
		if (Player->CanMove)
		{
			Player->CanMove = false;
		}
	}
}
