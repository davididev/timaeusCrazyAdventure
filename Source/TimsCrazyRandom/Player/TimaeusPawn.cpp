// Fill out your copyright notice in the Description page of Project Settings.


#include "TimsCrazyRandom/Player/TimaeusPawn.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Components/SkeletalMeshComponent.h"

// Sets default values
ATimaeusPawn::ATimaeusPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	PlayerMesh = CreateDefaultSubobject<USkeletalMeshComponent>("Player_Mesh");
	SpringArm = CreateDefaultSubobject<USpringArmComponent>("SpringArm");
	Camera = CreateDefaultSubobject<UCameraComponent>("Camera");



	RootComponent = PlayerMesh;
	SpringArm->SetupAttachment(PlayerMesh);
	Camera->SetupAttachment(SpringArm);

}

// Called when the game starts or when spawned
void ATimaeusPawn::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATimaeusPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ATimaeusPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

