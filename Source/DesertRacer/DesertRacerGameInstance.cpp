// Fill out your copyright notice in the Description page of Project Settings.


#include "DesertRacerGameInstance.h"

float UDesertRacerGameInstance::GetBestTime() const
{
	return BestTime;
}

FString UDesertRacerGameInstance::GetFormattedBestTime() const
{
	FTimespan TimeSpan = FTimespan(0, 0, BestTime);
	return TimeSpan.ToString(TEXT("%m:%s"));
}

bool UDesertRacerGameInstance::IsBestTimeSet() const
{
	return BestTime != 0;
}

void UDesertRacerGameInstance::SetBestTime(float fBestTime)
{
	BestTime = fBestTime;
}
