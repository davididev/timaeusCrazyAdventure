// Fill out your copyright notice in the Description page of Project Settings.


#include "TimsCrazyRandom/Player/PlayerGameInactiveWidget.h"
#include "TimsCrazyRandom/Player/GameModeBase_SideScroller.h"

void UPlayerGameInactiveWidget::SaveAndQuit()
{
	//TODO: Add functionality
}

void UPlayerGameInactiveWidget::QuitWithoutSaving()
{
	//TODO: Add functionality
}

void UPlayerGameInactiveWidget::ReturnToGame()
{
	AGameModeBase_SideScroller* GameMode = Cast<AGameModeBase_SideScroller>(GetWorld()->GetAuthGameMode());
	if (GameMode)
	{
		GameMode->SetUnpaused();
	}
}