#include "DesertRacerGameMode.h"

#include "DesertRacerGameInstance.h"
#include "Kismet/GameplayStatics.h"
#include "PlayerCharacter.h"

void ADesertRacerGameMode::ResetLevel(bool IsWin)
{
	float ResetTime = IsWin ? WinResetTime : LoseResetTime;
	GetWorldTimerManager().SetTimer(ResetGameTimer, this, &ADesertRacerGameMode::OnResetGameTimerTimeout, 1.f, false, ResetTime);
	if (IsWin)
	{
		SetBestTime();
	}
}

void ADesertRacerGameMode::SetBestTime()
{
	float GameTime = UGameplayStatics::GetRealTimeSeconds(GetWorld());
	UDesertRacerGameInstance* GameInstance = Cast<UDesertRacerGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));

	if (GameInstance != nullptr && !GameInstance->IsBestTimeSet() || GameTime < GameInstance->GetBestTime())
	{
		GameInstance->SetBestTime(GameTime);
		APlayerCharacter* Player = Cast<APlayerCharacter>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
		if (Player)
		{
			Player->NewHighScore();
		}
	}
}

void ADesertRacerGameMode::OnResetGameTimerTimeout()
{
	UGameplayStatics::OpenLevel(GetWorld(), FName("MainLevel"));
}
