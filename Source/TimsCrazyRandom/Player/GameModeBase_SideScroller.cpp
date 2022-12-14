// Fill out your copyright notice in the Description page of Project Settings.


#include "TimsCrazyRandom/Player/GameModeBase_SideScroller.h"
#include "Blueprint/UserWidget.h"
#include "TimsCrazyRandom/Player/PlayerGameActiveWidget.h"
#include "TimsCrazyRandom/Player/PlayerGameInactiveWidget.h"
#include "Kismet/GameplayStatics.h"

void AGameModeBase_SideScroller::BeginPlay()
{
	//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Orange, FString::Printf(TEXT("Begin play.")));
	SetUnpaused();
}

void AGameModeBase_SideScroller::SetUnpaused()
{
	if (GameWidgetClass)
	{
		//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Orange, FString::Printf(TEXT("Unpaused widget exists.")));
		UnpausedWidget = Cast<UPlayerGameActiveWidget>(CreateWidget(GetWorld(), GameWidgetClass));
		if (UnpausedWidget)
		{
			//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Orange, FString::Printf(TEXT("Cast successful.")));
			UGameplayStatics::SetGlobalTimeDilation(GetWorld(), 1.0f);
			UnpausedWidget->AddToViewport();
			UpdateUI();
		}
	}
}

void AGameModeBase_SideScroller::AddStar(int32 amt)
{
	Stars += amt;
	UpdateUI();
}

int32 AGameModeBase_SideScroller::GetStarCount()
{
	return Stars;
}

void AGameModeBase_SideScroller::RemoveHealth(int32 amt)
{
	Health -= amt;
	UpdateUI();
}

void AGameModeBase_SideScroller::LowerSecond()
{
	Timer--;
	UpdateUI();
}

void AGameModeBase_SideScroller::SetTime(int32 Time)
{
	Timer = Time;
	UpdateUI();
}

void AGameModeBase_SideScroller::SetAmmoType(int32 AT)
{
	AmmoType = AT;
}

int32 AGameModeBase_SideScroller::GetAmmoType()
{
	return AmmoType;
}

void AGameModeBase_SideScroller::SetPaused()
{
	if (GameWidgetClassPaused)
	{
		PausedWidget = Cast<UPlayerGameInactiveWidget>(CreateWidget(GetWorld(), GameWidgetClassPaused));
		if (PausedWidget)
		{
			UGameplayStatics::SetGlobalTimeDilation(GetWorld(), 0.0f);
			PausedWidget->AddToViewport();
		}
	}
}

void AGameModeBase_SideScroller::UpdateUI()
{
	if (UnpausedWidget)
	{
		float perc = (100.0f * Health / MAX_HEALTH) / 100.0f;
		UnpausedWidget->SetHealth(perc);
		UnpausedWidget->SetStars(Stars);
		UnpausedWidget->SetTime(Timer);
	}
}