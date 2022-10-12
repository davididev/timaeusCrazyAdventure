// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ItemBox.generated.h"

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
	UPROPERTY(EditAnywhere, Category = "Components")
	UStaticMeshComponent* BoxObj;
	UPROPERTY(EditAnywhere, Category = "Components")
	AActor* WhatToSpawn;
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	void PlayerHitBox(FVector Normal);
};
