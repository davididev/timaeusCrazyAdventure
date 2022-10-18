// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ItemBox.generated.h"
class AGameModeBase_SideScroller;

UCLASS()
class TIMSCRAZYRANDOM_API AItemBox : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AItemBox();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	AGameModeBase_SideScroller* GameMode;
	UPROPERTY(EditAnywhere, Category = "Components")
	UStaticMeshComponent* BoxObj;
	UPROPERTY(EditAnywhere, Category = "Components")
		UStaticMeshComponent* WhatToSpawn;
	UPROPERTY(EditAnywhere, Category = "Param")
		UAudioComponent* SoundSource;
	UPROPERTY(EditAnywhere, Category = "Param")
		int32 AmmoType = 1;

	FVector WhatToSpawnLocalPositionTarget;
	int WhatToSpawnStep = 0;
	const float WHAT_TO_SPAWN_MOVE_PER_SECOND = 250.0f;
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	void PlayerHitBox(FVector Normal);
};
