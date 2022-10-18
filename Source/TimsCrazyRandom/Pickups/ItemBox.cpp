// Fill out your copyright notice in the Description page of Project Settings.


#include "TimsCrazyRandom/Pickups/ItemBox.h"
#include "Math/UnrealMathUtility.h"
#include "Components/AudioComponent.h"
#include "TimsCrazyRandom/Player/GameModeBase_SideScroller.h"

// Sets default values
AItemBox::AItemBox()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	BoxObj = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Item Box"));
	WhatToSpawn = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PreviewToSpawn"));
	SoundSource = CreateDefaultSubobject< UAudioComponent>("SoundFX");
	
	RootComponent = BoxObj;
	WhatToSpawn->SetupAttachment(BoxObj);
	SoundSource->SetupAttachment(BoxObj);
	
}

// Called when the game starts or when spawned
void AItemBox::BeginPlay()
{
	Super::BeginPlay();
	GameMode = Cast<AGameModeBase_SideScroller>(GetWorld()->GetAuthGameMode());
}

// Called every frame
void AItemBox::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	FVector temp = WhatToSpawn->GetRelativeLocation();
	if (WhatToSpawnStep == 1)
	{
		temp = FMath::VInterpConstantTo(temp, WhatToSpawnLocalPositionTarget, DeltaTime, WHAT_TO_SPAWN_MOVE_PER_SECOND);
		WhatToSpawn->SetRelativeLocation(temp);
		if (temp == WhatToSpawnLocalPositionTarget)
		{
			WhatToSpawnStep = 2;
			WhatToSpawnLocalPositionTarget = FVector(0.0f, 0.0f, 0.0f);
			return;
		}
	}
	if (WhatToSpawnStep == 2)
	{
		temp = FMath::VInterpConstantTo(temp, WhatToSpawnLocalPositionTarget, DeltaTime, WHAT_TO_SPAWN_MOVE_PER_SECOND);
		WhatToSpawn->SetRelativeLocation(temp);
		if (temp == WhatToSpawnLocalPositionTarget)
		{
			WhatToSpawnStep = 0;
		}
	}
}

void AItemBox::PlayerHitBox(FVector Normal)
{
	if (WhatToSpawn == nullptr)
		return;
	if (Normal.Z < -0.2f)  //Hit from below
	{
		WhatToSpawnStep = 1;
		WhatToSpawnLocalPositionTarget = FVector(0.0f, 0.0f, 250.0f);
		SoundSource->Play();
		if (GameMode)
			GameMode->SetAmmoType(AmmoType);
		//FVector v = this->GetActorLocation() + FVector(0.0, 0.0, 1.0);
		//FRotator r = FRotator();
		//AActor* myResult = GetWorld()->SpawnActor(WhatToSpawn->StaticClass(), &v, &r);
		//Destroy();
	}
}

