// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "DesertRacerGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class DESERTRACER_API UDesertRacerGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	float GetBestTime() const;

	UFUNCTION(BlueprintPure)
	FString GetFormattedBestTime() const;

	UFUNCTION(BlueprintPure)
	bool IsBestTimeSet() const;

	void SetBestTime(float fBestTime);

private:
	UPROPERTY(VisibleAnywhere)
	float BestTime = 0;
};
