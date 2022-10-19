// Fill out your copyright notice in the Description page of Project Settings.


#include "TimsCrazyRandom/Enemy/EnemyBase.h"
#include "Components/SkeletalMeshComponent.h"
#include "Animation/AnimationAsset.h"
#include "Components/AudioComponent.h"
#include "Sound/SoundBase.h"

// Sets default values
AEnemyBase::AEnemyBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	RootMesh = CreateDefaultSubobject<USkeletalMeshComponent>("RootMesh");
	RootComponent = RootMesh;
}

// Called when the game starts or when spawned
void AEnemyBase::BeginPlay()
{
	Super::BeginPlay();
	
}


void AEnemyBase::OnStep(float DeltaTime)
{
}

void AEnemyBase::ProcessBrains()
{
}

// Called every frame
void AEnemyBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	ProcessBrains();
	OnStep(DeltaTime);
}

void AEnemyBase::FireBullet()
{
}

void AEnemyBase::SetBrain(int32 BID, float StepTimer)
{
	BrainID = BID;
	BrainStep = 0;
	BrainTimer = 0.0f;
	BrainStepTime = StepTimer;
}

