// Fill out your copyright notice in the Description page of Project Settings.


#include "TimsCrazyRandom/Shared/Bullet.h"
#include "Components/AudioComponent.h"
#include "Sound/SoundBase.h"
#include "TimsCrazyRandom/Player/TimaeusPawn.h"
#include "TimsCrazyRandom/Enemy/EnemyBase.h"

// Sets default values
ABullet::ABullet()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	RootMesh = CreateDefaultSubobject<UStaticMeshComponent>("RootMesh");
	SoundSource = CreateDefaultSubobject<UAudioComponent>("Sound_Src");
	RootMesh->SetSimulatePhysics(true); 

	RootMesh->OnComponentBeginOverlap.AddDynamic(this, &ABullet::OnTrigger);
	RootMesh->OnComponentHit.AddDynamic(this, &ABullet::OnHit);

	RootComponent = RootMesh;
	SoundSource->SetupAttachment(RootMesh);
}

// Called when the game starts or when spawned
void ABullet::BeginPlay()
{
	Super::BeginPlay();
	RootMesh->AddImpulse(FVector(0.0, 0.0, 100.0));
	PlaySound(ThrowSound);
	DeathTimer = 15.0f;  //In case it goes on perpetually without hitting anything
}

void ABullet::OnTrigger(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	//TODO: Add damaging code
	if (TargetPlayer == true)
	{
		ATimaeusPawn* Tim = Cast<ATimaeusPawn>(OtherActor);
		if (Tim)
		{
			Tim->TryDamage(DamageAmount);
			PlaySound(HitTargetSound);
			DeathTimer = HitTargetSound->GetDuration();
			HitSomething = true;
		}
	}
	else  //Target enemy
	{
		AEnemyBase* Enem = Cast<AEnemyBase>(OtherActor);
		if(Enem)
		{
			Enem->OnDamage(DamageAmount);
			PlaySound(HitTargetSound);
			DeathTimer = HitTargetSound->GetDuration();
			HitSomething = true;
		}
	}
}

void ABullet::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	HitSomething = true;
	PlaySound(HitWallSound);
	DeathTimer = HitWallSound->GetDuration();
}

void ABullet::PlaySound(USoundBase* snd)
{
	if (snd)
	{
		SoundSource->SetSound(snd);
		SoundSource->Play();
	}
}

// Called every frame
void ABullet::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	if (HitSomething == false)
	{
		RootMesh->AddForce(FVector(MoveDirection * MoveVelocity * RootMesh->GetMass(), 0.0, 0.0));
		RootMesh->AddLocalRotation(FRotator(0.0, 0.0, SpinSpeed * DeltaTime));
	}
	

	if (DeathTimer > 0.0f)
	{
		DeathTimer -= DeltaTime;
		if (DeathTimer <= 0.0f)
			Destroy();
	}
	
}

void ABullet::SetDirection(double Dir)
{
	MoveDirection = Dir;
	RootMesh->SetRelativeRotation(FRotator(0.0, 90.0, 0.0));
}

