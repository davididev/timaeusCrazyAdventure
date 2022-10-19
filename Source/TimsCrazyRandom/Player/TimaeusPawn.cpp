// Fill out your copyright notice in the Description page of Project Settings.


#include "TimsCrazyRandom/Player/TimaeusPawn.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Animation/AnimationAsset.h"
#include "Components/CapsuleComponent.h"
#include "Math/UnrealMathUtility.h"
#include "TimsCrazyRandom/Pickups/ItemBox.h"
#include "Components/AudioComponent.h"
#include "Sound/SoundBase.h"
#include "TimsCrazyRandom/Player/GameModeBase_SideScroller.h"
#include "TimsCrazyRandom/Shared/Bullet.h"


// Sets default values
ATimaeusPawn::ATimaeusPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	PlayerCollider = CreateDefaultSubobject< UCapsuleComponent>("Collider");

	PlayerMesh = CreateDefaultSubobject<USkeletalMeshComponent>("Player_Mesh");
	SpringArm = CreateDefaultSubobject<USpringArmComponent>("SpringArm");
	Camera = CreateDefaultSubobject<UCameraComponent>("Camera");
	SoundSource = CreateDefaultSubobject<UAudioComponent>("Sound FX");
	MusicSource = CreateDefaultSubobject<UAudioComponent>("Music FX");

	RootComponent = PlayerCollider;
	PlayerMesh->SetupAttachment(PlayerCollider);
	SoundSource->SetupAttachment(PlayerMesh);
	MusicSource->SetupAttachment(PlayerMesh);
	SpringArm->SetupAttachment(PlayerMesh);
	Camera->SetupAttachment(SpringArm);

}

// Called when the game starts or when spawned
void ATimaeusPawn::BeginPlay()
{
	Super::BeginPlay();
	PlayerCollider->OnComponentHit.AddDynamic(this, &ATimaeusPawn::OnHit);

	GameMode = Cast<AGameModeBase_SideScroller>(GetWorld()->GetAuthGameMode());
}

void ATimaeusPawn::MoveHorizontal(float axis)
{
	FVector vel = PlayerCollider->ComponentVelocity;
	if (FMath::Abs(vel.X) < MaxVelocity)
	{
		//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Orange, FString::Printf(TEXT("Z Lol: %f"), axis));
		PlayerCollider->AddForce(FVector(axis * MoveForce * PlayerCollider->GetMass(), 0.0, 0.0));
	}
	if (axis < -0.5f)
		RotationTarget = 90.0;
	if (axis > 0.5f)
		RotationTarget = 270.0;
}

void ATimaeusPawn::JumpPressed()
{
	FHitResult OutHit;
	FVector Start = GetActorLocation();

	FVector End = FVector(0.0f, 0.0f, -150.0f) + Start;
	FCollisionQueryParams CollisionParams;
	//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Orange, FString::Printf(TEXT("Start %f %f %f."), Start.X, Start.Y, Start.Z));
	//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Orange, FString::Printf(TEXT("End %f %f %f."), End.X, End.Y, End.Z));

	bool isGrounded = ActorLineTraceSingle(OutHit, Start, End, ECC_WorldStatic, CollisionParams);

	if (OutHit.GetActor())
	{
		SoundSource->SetSound(JumpSoundFX);
		SoundSource->Play();
		PlayerCollider->AddImpulse(FVector::UpVector * JumpForce * PlayerCollider->GetMass());
	}

}

void ATimaeusPawn::JumpReleased()
{
	FVector vel = PlayerCollider->ComponentVelocity;
	if (vel.Z > 0.0f)
	{
		vel.Z = 0.0f;
		PlayerCollider->SetPhysicsLinearVelocity(vel);
	}
}

void ATimaeusPawn::AttackPressed()
{
	double direction = 0.0;
	if (FMath::IsNearlyEqual(RotationTarget, 90.0))
		direction = -1.0;
	if (FMath::IsNearlyEqual(RotationTarget, 270.0))
		direction = 1.0;
	if (GameMode)
	{
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Orange, FString::Printf(TEXT("Game Mode found")));
		if (GameMode->GetStarCount() > 0)
		{
			FTransform SpawnLocation;
			SpawnLocation.SetLocation(GetActorLocation());

			FActorSpawnParameters param;

			if (GameMode->GetAmmoType() == 1)
			{
				GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Orange, FString::Printf(TEXT("Shirkuyn seledcted")));
				
				AActor* temp = GetWorld()->SpawnActor(ShirukenPrefab, &SpawnLocation, param);
				if (temp)
				{
					ABullet* bullet = Cast<ABullet>(temp);
					if (bullet)
					{
						GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Orange, FString::Printf(TEXT("Bullet cast success")));
						bullet->SetDirection(direction);
						GameMode->AddStar(-1);
					}
				}
				
					
			}
		}
		
	}
}

void ATimaeusPawn::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	AItemBox* ItemBox = Cast< AItemBox>(OtherActor);
	if (ItemBox)
	{
		ItemBox->PlayerHitBox(Hit.Normal);
	}
}

// Called every frame
void ATimaeusPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	FRotator tempRot = PlayerMesh->GetRelativeRotation();
	tempRot.Yaw = FMath::FixedTurn(tempRot.Yaw, RotationTarget, DeltaTime * RotatePerSecond);
	PlayerMesh->SetRelativeRotation(tempRot);
	MiniTimer += DeltaTime;
	if (MiniTimer >= 1.0)
	{
		MiniTimer -= 1.0;
		if (GameMode)
			GameMode->LowerSecond();
	}
}

// Called to bind functionality to input
void ATimaeusPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAxis("MoveHorizontal", this, &ATimaeusPawn::MoveHorizontal);
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ATimaeusPawn::JumpPressed);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ATimaeusPawn::JumpReleased);
	PlayerInputComponent->BindAction("Attack", IE_Pressed, this, &ATimaeusPawn::AttackPressed);

}

void ATimaeusPawn::PlayMusic(USoundBase* MyAudioClip)
{
	MusicSource->SetSound(MyAudioClip);
	MusicSource->Play();
	
}

void ATimaeusPawn::TryDamage(int32 Amt)
{
}

void ATimaeusPawn::DamageOverride(int32 Amt)
{
}

