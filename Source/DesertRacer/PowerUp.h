#pragma once

#include "Components/CapsuleComponent.h"
#include "CoreMinimal.h"
#include "Engine/TimerHandle.h"
#include "GameFramework/Actor.h"
#include "PaperSpriteComponent.h"
#include "Sound/SoundBase.h"
#include "PowerUp.generated.h"

UCLASS()
class DESERTRACER_API APowerUp : public AActor
{
	GENERATED_BODY()

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	UCapsuleComponent* CapsuleComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	UPaperSpriteComponent* PowerUpSprite;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USoundBase* HitSound;

	UPROPERTY(EditAnywhere)
	float EffectTime = 2.f;

	UPROPERTY(EditAnywhere)
	float TurnRate = 60.f;

	FTimerHandle PowerUpTimer;

	APowerUp();

	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

	void Rotate(float DeltaTime);

	UFUNCTION()
	void OverlapBegin(
		UPrimitiveComponent* OverlappedComponent,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex,
		bool FromSweep,
		const FHitResult& SweepResult);

	void EndEffect();
};
