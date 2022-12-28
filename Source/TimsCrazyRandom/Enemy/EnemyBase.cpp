// Fill out your copyright notice in the Description page of Project Settings.


#include "TimsCrazyRandom/Enemy/EnemyBase.h"
#include "Components/SkeletalMeshComponent.h"
#include "Animation/AnimationAsset.h"
#include "Components/AudioComponent.h"
#include "Sound/SoundBase.h"
#include "TimsCrazyRandom/Player/TimaeusPawn.h"
#include "Materials/MaterialInterface.h"
#include "Components/CapsuleComponent.h"
#include "EnemyBase.h"

// Sets default values
AEnemyBase::AEnemyBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	MainCollider = CreateDefaultSubobject<UCapsuleComponent>("RootCollider");
	RootMesh = CreateDefaultSubobject<USkeletalMeshComponent>("RootMesh");
	RootComponent = MainCollider;
	RootMesh->SetupAttachment(MainCollider);


	VectorGlowName = FName(TEXT("FlashColor"));
	VectorGlowValue = FVector(0.0, 0.0, 0.0);
	
}

// Called when the game starts or when spawned
void AEnemyBase::BeginPlay()
{
	Super::BeginPlay();
	IsGroundedTime = GetWorld()->TimeSeconds + 0.1;
	MainCollider->OnComponentHit.AddDynamic(this, &AEnemyBase::OnCollision);
}

void AEnemyBase::OnCollision(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	if (Hit.Normal.Z > 0.5)
	{
		IsGroundedTime = GetWorld()->TimeSeconds + 0.1;
		//GEngine->AddOnScreenDebugMessage(-1, 15.0, FColor::Orange, FString::Printf(TEXT("Grounded!")));
	}

}

bool AEnemyBase::IsGrounded()
{
	return (GetWorld()->TimeSeconds < IsGroundedTime);
}


void AEnemyBase::OnStep(float DeltaTime)
{
}

void AEnemyBase::ProcessBrains()
{
}

void AEnemyBase::ProcessDamageFlash()
{
	if (DmgTimer > 0.0f)
	{
		double perc = FMath::Cos(FMath::DegreesToRadians(360.0 / DmgTimer * DamageTime));
		perc += 1.0;
		perc *= 0.5;
		VectorGlowValue.Set(perc, 0.0, 0.0);
	}
	else
	{
		VectorGlowValue.Set(0.0, 0.0, 0.0);
	}
	if (RootMesh)
	{
		RootMesh->SetVectorParameterValueOnMaterials(VectorGlowName, VectorGlowValue);
	}
	

}

// Called every frame
void AEnemyBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	ProcessBrains();
	ProcessDamageFlash();
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

void AEnemyBase::OnPlayerHit(FVector Normal, ATimaeusPawn *Timaeus)
{
	bool DamageSelf = false;
	if (CanJumpOnTop)
	{
		if (Normal.Z > 0.15f)
			DamageSelf = true;  //You hit the top of the enemy and they don't have a spike or anything
	}

	if (DamageSelf)
		OnDamage(1);
	else
		Timaeus->TryDamage(TouchDamage);
}

void AEnemyBase::OnDamage(int32 Amt)
{
	if (DmgTimer > 0.0f)
	{
		Health -= Amt;
		if (Health > 0)
		{
			DmgTimer = DamageTime;
		}
		else
		{
			Destroy();
		}
	}
}

