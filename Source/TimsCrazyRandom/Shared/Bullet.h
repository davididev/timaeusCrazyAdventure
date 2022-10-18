// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Bullet.generated.h"
class UAudioComponent;
class USoundBase;

UCLASS()
class TIMSCRAZYRANDOM_API ABullet : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABullet();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Parameters")
		bool TargetPlayer = false;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Parameters")
		float MoveVelocity = 600.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Parameters")
		float SpinSpeed = 360.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Parameters")
		int32 DamageAmount = 1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
		UStaticMeshComponent* RootMesh;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
		UAudioComponent* SoundSource;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
		USoundBase* ThrowSound;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
		USoundBase* HitTargetSound;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
		USoundBase* HitWallSound;
	
	double MoveDirection = 0.0;
	float DeathTimer = -1.0f;
	bool HitSomething = false;

	UFUNCTION()
		void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	UFUNCTION()
		void OnTrigger(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	void PlaySound(USoundBase* snd);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	void SetDirection(double Dir);
};
