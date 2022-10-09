// Fill out your copyright notice in the Description page of Project Settings.


#include "TimsCrazyRandom/Pickups/StarPickup.h"
#include "TimsCrazyRandom/Player/GameModeBase_SideScroller.h"

void AStarPickup::CustomOverlapCode()
{
	AGameModeBase_SideScroller* GameMode = Cast<AGameModeBase_SideScroller>(GetWorld()->GetAuthGameMode());
	if (GameMode)
	{
		GameMode->AddStar(1);
	}
}