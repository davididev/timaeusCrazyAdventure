// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TimsCrazyRandom/Pickups/PickupBase.h"
#include "StarPickup.generated.h"

/**
 * 
 */
UCLASS()
class TIMSCRAZYRANDOM_API AStarPickup : public APickupBase
{
	GENERATED_BODY()
protected:
	void CustomOverlapCode() override;
};
