#include "DesertRacerGameMode.h"

#include "Kismet/GameplayStatics.h"

void ADesertRacerGameMode::ResetLevel(bool IsWin)
{
	float ResetTime = IsWin ? WinResetTime : LoseResetTime;
	GetWorldTimerManager().SetTimer(ResetGameTimer, this, &ADesertRacerGameMode::OnResetGameTimerTimeout, 1.f, false, ResetTime);
}

void ADesertRacerGameMode::OnResetGameTimerTimeout()
{
	UGameplayStatics::OpenLevel(GetWorld(), FName("MainLevel"));
}
