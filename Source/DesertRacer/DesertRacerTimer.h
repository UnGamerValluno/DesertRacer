// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "DesertRacerTimer.generated.h"

/**
 * 
 */
UCLASS()
class DESERTRACER_API UDesertRacerTimer : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintImplementableEvent)
	void NewHighScoreAnimation();
};
