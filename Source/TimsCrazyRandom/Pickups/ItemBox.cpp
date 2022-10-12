// Fill out your copyright notice in the Description page of Project Settings.


#include "TimsCrazyRandom/Pickups/ItemBox.h"

// Sets default values
AItemBox::AItemBox()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	BoxObj = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Item Box"));
	RootComponent = BoxObj;
}

// Called when the game starts or when spawned
void AItemBox::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AItemBox::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AItemBox::PlayerHitBox(FVector Normal)
{
	if (WhatToSpawn == nullptr)
		return;
	if (Normal.Z < -0.2f)  //Hit from below
	{
		FVector v = this->GetActorLocation() + FVector(0.0, 0.0, 1.0);
		FRotator r = FRotator();
		AActor* myResult = GetWorld()->SpawnActor(WhatToSpawn->StaticClass(), &v, &r);
		Destroy();
	}
}

