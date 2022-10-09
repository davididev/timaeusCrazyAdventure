// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PlayerGameInactiveWidget.generated.h"

/**
 * 
 */
UCLASS()
class TIMSCRAZYRANDOM_API UPlayerGameInactiveWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	void SaveAndQuit();
	void QuitWithoutSaving();
	void ReturnToGame();

};
