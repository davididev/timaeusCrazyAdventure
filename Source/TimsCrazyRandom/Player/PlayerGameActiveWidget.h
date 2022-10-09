// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PlayerGameActiveWidget.generated.h"

/**
 * 
 */
UCLASS()
class TIMSCRAZYRANDOM_API UPlayerGameActiveWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintImplementableEvent)
		void SetStars(int32 StarCount);
	UFUNCTION(BlueprintImplementableEvent)
		void SetHealth(float HealthPerc);
};
