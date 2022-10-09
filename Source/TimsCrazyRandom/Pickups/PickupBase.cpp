// Fill out your copyright notice in the Description page of Project Settings.


#include "TimsCrazyRandom/Pickups/PickupBase.h"
#include "Kismet/GameplayStatics.h"
#include "Components/AudioComponent.h"
#include "TimsCrazyRandom/Player/TimaeusPawn.h"

// Sets default values
APickupBase::APickupBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>("MainModel");
	StaticMesh->OnComponentBeginOverlap.AddDynamic(this, &APickupBase::BeginOverlap);

	SoundFXOnCollect = CreateDefaultSubobject< UAudioComponent>("Sound FX");

	RootComponent = StaticMesh;
	
	SoundFXOnCollect->SetupAttachment(StaticMesh);
}

void APickupBase::BeginOverlap(UPrimitiveComponent* OverlappedComponent,
	AActor* OtherActor,
	UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex,
	bool bFromSweep,
	const FHitResult& SweepResult)
{
	if (DeathTimer == true)
		return;
	if (Cast<ATimaeusPawn>(OtherActor) != nullptr)
	{
		if(SoundFXOnCollect)
			SoundFXOnCollect->Play();
		DeathTimer = true;
		CustomOverlapCode();
		
	}
}

void APickupBase::CustomOverlapCode()
{
}


// Called when the game starts or when spawned
void APickupBase::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APickupBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (DeathTimer)  //Dying sound effect
	{
		StaticMesh->AddLocalRotation(FRotator(0.0, RotateSpeed * DeltaTime * 10.0, 0.0));
		if (SoundFXOnCollect == nullptr)
		{
			this->Destroy();
		}
		else

		{
			if (SoundFXOnCollect->IsPlaying() == false)
			{
				this->Destroy();
			}
		}
		
	}
	else //Normal process
	{
		//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Orange, FString::Printf(TEXT("Normal process.")));
		StaticMesh->AddLocalRotation(FRotator(0.0, RotateSpeed * DeltaTime, 0.0));
	}
}

