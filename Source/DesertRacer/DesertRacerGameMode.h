#pragma once

#include "CoreMinimal.h"
#include "Engine/TimerHandle.h"
#include "GameFramework/GameModeBase.h"
#include "DesertRacerGameMode.generated.h"

UCLASS()
class DESERTRACER_API ADesertRacerGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float LoseResetTime = 1.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float WinResetTime = 3.f;

	FTimerHandle ResetGameTimer;

	void ResetLevel(bool IsWin);
	void SetBestTime();
	void OnResetGameTimerTimeout();
};
