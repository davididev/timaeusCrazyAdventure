// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SceneVars.generated.h"

class USoundBase;

UCLASS()
class TIMSCRAZYRANDOM_API ASceneVars : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASceneVars();
	UPROPERTY(EditAnywhere, Category = "Scene_Vars")
		USoundBase* MusicClip;
	UPROPERTY(EditAnywhere, Category = "Scene_Vars")
		int32 LevelSeconds = 100;

	UPROPERTY(EditAnywhere, Category = "Scene_Vars")
		UStaticMeshComponent* MyRoot;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	bool Started = false;
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
