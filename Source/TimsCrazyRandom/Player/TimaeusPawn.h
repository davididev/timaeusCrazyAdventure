// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "TimaeusPawn.generated.h"

class USkeletalMeshComponent;
class USpringArmComponent;
class UCameraComponent;
class UCapsuleComponent;
class UAudioComponent;
class USoundBase;
class AGameModeBase_SideScroller;
class ABullet;

UCLASS()
class TIMSCRAZYRANDOM_API ATimaeusPawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ATimaeusPawn();
	

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	AGameModeBase_SideScroller* GameMode;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
		UCapsuleComponent* PlayerCollider;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
		USkeletalMeshComponent* PlayerMesh;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
		USpringArmComponent* SpringArm;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
		UCameraComponent* Camera;

	UPROPERTY(EditAnywhere, Category = "Components")
		UAudioComponent* SoundSource;

	UPROPERTY(EditAnywhere, Category = "Components")
		UAudioComponent* MusicSource;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Parameters")
		float MoveForce = 500.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Parameters")
		float MaxVelocity = 8.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Parameters")
		float JumpForce = 1000.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Parameters")
		float RotatePerSecond = 360.0f;

	UPROPERTY(EditAnywhere, Category = "Sound_FX")
		USoundBase* JumpSoundFX;


	float RotationTarget = 0.0;
	float MiniTimer = 0.0f;  //Timer in between seconds int
	float DamageTimer = -1.0f;

	void MoveHorizontal(float axis);
	void JumpPressed();
	void JumpReleased();
	void AttackPressed();

	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void PlayMusic(USoundBase* MyAudioClip);

	void TryDamage(int32 Amt);
	void DamageOverride(int32 Amt);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Classes)
		TSubclassOf<ABullet> ShirukenPrefab;

	

};
