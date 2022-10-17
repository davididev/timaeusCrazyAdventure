// Fill out your copyright notice in the Description page of Project Settings.


#include "TimsCrazyRandom/Player/SceneVars.h"
#include "TimsCrazyRandom/Player/GameModeBase_SideScroller.h"
#include "TimsCrazyRandom/Player/TimaeusPawn.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ASceneVars::ASceneVars()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	MyRoot = CreateDefaultSubobject<UStaticMeshComponent>("KEEP_BLANK");
	RootComponent = MyRoot;

}

// Called when the game starts or when spawned
void ASceneVars::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASceneVars::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (!Started)
	{
		AGameModeBase_SideScroller* GameMode = Cast<AGameModeBase_SideScroller>(GetWorld()->GetAuthGameMode());
		if (GameMode)
		{
			GameMode->SetTime(LevelSeconds);
			AActor* TimTemp = UGameplayStatics::GetActorOfClass(this, ATimaeusPawn::StaticClass());
			ATimaeusPawn* Tim = Cast<ATimaeusPawn>(TimTemp);
			if (Tim)
			{
				Tim->PlayMusic(MusicClip);
				Started = true;
			}
			
		}
	}
}

