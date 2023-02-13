// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EnemyBase.generated.h"

class USkeletalMeshComponent;
class UAnimationAsset;
class ABullet;
class UAudioComponent;
class USoundBase;
class ATimaeusPawn;
class UCapsuleComponent;

UCLASS()
class TIMSCRAZYRANDOM_API AEnemyBase : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AEnemyBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Parameters")
		int32 Health = 2;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Parameters")
		int32 TouchDamage = 1;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Parameters")
		float DamageTime = 1.0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Parameters")
		bool CanJumpOnTop = true;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Parameters")
		float MoveForce = 400.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Parameters")
		float JumpImpulse = 200.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
		UCapsuleComponent* MainCollider;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
		USkeletalMeshComponent* RootMesh;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
		UAudioComponent* SoundSource;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animations")
		UAnimationAsset* IdleAnimation;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animations")
		UAnimationAsset* WalkAnimation;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animations")
		UAnimationAsset* JumpAnimation;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animations")
		UAnimationAsset* ShootBulletAnimation;
	
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sounds")
		USoundBase* JumpSound;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Classes)
		TSubclassOf<ABullet> BulletPrefab;

	virtual void OnStep(float DeltaTime);
private:
	int32 BrainID = 0;
	int32 BrainStep = 0;
	float BrainTimer = 0.0f;
	float BrainStepTime = 0.0f;  //Time for any delays in the brain, mostly for jumping up and down.
	float IsGroundedTime = 0.0f;
	float RotateTarget = 90.0;
	void ProcessBrains(float DeltaTime);
	void ProcessDamageFlash(float DeltaTime);
	float DmgTimer = 0.0f;
	FName VectorGlowName;
	FVector VectorGlowValue;
	bool started = false;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	UFUNCTION(blueprintcallable)
	void FireBullet();
	UFUNCTION(blueprintcallable)
	void SetBrain(int32 BID, float StepTimer);
	const int32 BRAIN_IDLE = 0;
	const int32 BRAIN_WALK_LEFT_RIGHT = 1;
	const int32 BRAIN_JUMP_UP_DOWN = 2;
	const int32 BRAIN_FOLLOW_PLAYER = 3;
	bool IsGrounded();

	void OnPlayerHit(FVector Normal, ATimaeusPawn* Timaeus);  //Should be called by player
	void OnDamage(int32 Amt);

	UFUNCTION(BlueprintImplementableEvent)
		void BeginEnemy();
};
