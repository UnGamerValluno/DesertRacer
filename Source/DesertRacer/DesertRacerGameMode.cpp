#include "DesertRacerGameMode.h"

#include "DesertRacerGameInstance.h"
#include "Kismet/GameplayStatics.h"

void ADesertRacerGameMode::ResetLevel(bool IsWin)
{
	UE_LOG(LogTemp, Warning, TEXT("aqui 0 %s"), IsWin ? TEXT("true") : TEXT("false"));
	float ResetTime = IsWin ? WinResetTime : LoseResetTime;
	GetWorldTimerManager().SetTimer(ResetGameTimer, this, &ADesertRacerGameMode::OnResetGameTimerTimeout, 1.f, false, ResetTime);
	if (IsWin)
	{
		SetBestTime();
	}
}

void ADesertRacerGameMode::SetBestTime()
{
	UE_LOG(LogTemp, Warning, TEXT("aqui 1"));
	float GameTime = UGameplayStatics::GetRealTimeSeconds(GetWorld());
	UDesertRacerGameInstance* GameInstance = Cast<UDesertRacerGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));

	UE_LOG(LogTemp, Warning, TEXT("aqui 2"));
	if (GameInstance != nullptr && !GameInstance->IsBestTimeSet() || GameTime < GameInstance->GetBestTime())
	{
		UE_LOG(LogTemp, Warning, TEXT("si pongo el time"));
		GameInstance->SetBestTime(GameTime);
	}
}

void ADesertRacerGameMode::OnResetGameTimerTimeout()
{
	UGameplayStatics::OpenLevel(GetWorld(), FName("MainLevel"));
}
