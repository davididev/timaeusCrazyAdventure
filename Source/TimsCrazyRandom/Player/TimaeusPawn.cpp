// Fill out your copyright notice in the Description page of Project Settings.


#include "TimsCrazyRandom/Player/TimaeusPawn.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/AudioComponent.h"
#include "Math/UnrealMathUtility.h"

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


	RootComponent = PlayerCollider;
	PlayerMesh->SetupAttachment(PlayerCollider);
	SoundSource->SetupAttachment(PlayerMesh);
	SpringArm->SetupAttachment(PlayerMesh);
	Camera->SetupAttachment(SpringArm);

}

// Called when the game starts or when spawned
void ATimaeusPawn::BeginPlay()
{
	Super::BeginPlay();
	
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

	FVector End = FVector(0.0f, 0.0f, PlayerCollider->GetScaledCapsuleHalfHeight() * -1.05f) + Start;
	FCollisionQueryParams CollisionParams;

	bool isGrounded = ActorLineTraceSingle(OutHit, Start, End, ECC_WorldStatic, CollisionParams);

	if (isGrounded)
	{
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
}

// Called every frame
void ATimaeusPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	FRotator tempRot = PlayerMesh->GetRelativeRotation();
	tempRot.Yaw = FMath::FixedTurn(tempRot.Yaw, RotationTarget, DeltaTime * RotatePerSecond);
	//tempRot = FMath::RInterpConstantTo(tempRot, targetRot, DeltaTime, RotatePerSecond);
	PlayerMesh->SetRelativeRotation(tempRot);
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

