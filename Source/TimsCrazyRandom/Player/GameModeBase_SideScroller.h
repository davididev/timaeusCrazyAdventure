// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "GameModeBase_SideScroller.generated.h"

class UUserWidget;
class UPlayerGameActiveWidget;
class UPlayerGameInactiveWidget;

/**
 * 
 */
UCLASS()
class TIMSCRAZYRANDOM_API AGameModeBase_SideScroller : public AGameModeBase
{
	GENERATED_BODY()
public:
	const int32 MAX_HEALTH = 3;
protected:
	int32 Stars = 0;
	int32 Timer = 100;
	int32 Health = MAX_HEALTH;
	UPROPERTY(EditAnywhere, Category = "Widgets")
		TSubclassOf<class UUserWidget> GameWidgetClass;
	UPROPERTY(EditAnywhere, Category = "Widgets")
		TSubclassOf<class UUserWidget> GameWidgetClassPaused;

	UPROPERTY()
		UPlayerGameActiveWidget* UnpausedWidget;
	UPROPERTY()
		UPlayerGameInactiveWidget* PausedWidget;

	//TODO: Add a paused widget

	virtual void BeginPlay() override;


public:
	void UpdateUI();
	void SetPaused();
	void SetUnpaused();
	void AddStar(int amt);
	void RemoveHealth(int amt);
	void LowerSecond();
	void SetTime(int32 Time);
};
