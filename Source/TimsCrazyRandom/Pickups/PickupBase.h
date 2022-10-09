// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PickupBase.generated.h"

class UGameplayStatics;
class UAudioComponent;

UCLASS()
class TIMSCRAZYRANDOM_API APickupBase : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APickupBase();
private:
	bool DeathTimer = false;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, Category = "Param")
		double RotateSpeed = 180.0;
	UPROPERTY(EditAnywhere, Category = "Param")
		UAudioComponent* SoundFXOnCollect;

	UPROPERTY(EditAnywhere, Category = "Param")
		UStaticMeshComponent* StaticMesh;

	UFUNCTION()
	void BeginOverlap(UPrimitiveComponent* OverlappedComponent,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex,
		bool bFromSweep,
		const FHitResult& SweepResult);

	virtual void CustomOverlapCode();
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
