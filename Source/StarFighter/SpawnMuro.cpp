// Fill out your copyright notice in the Description page of Project Settings.


#include "SpawnMuro.h"

// Sets default values
ASpawnMuro::ASpawnMuro()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SpawnLocation = CreateDefaultSubobject<USceneComponent>("SpawnLocation");
}

// Called when the game starts or when spawned
void ASpawnMuro::BeginPlay()
{
	Super::BeginPlay();
	SpawnMuro();
	
}

// Called every frame
void ASpawnMuro::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


void ASpawnMuro::PickupCollected()
{
	GetWorld()->GetTimerManager().SetTimer(MyTimer, this, & ASpawnMuro::SpawnMuro, 3, false);

	CurrentPickup->OnPickedUp.Unbind();
	CurrentPickup->Destroy();

}

void ASpawnMuro::SpawnMuro()
{
	UWorld* MyWorld = GetWorld();
	if (MyWorld != nullptr)
	{
		CurrentPickup = MyWorld->SpawnActor<AMuroMove>(AMuroMove::StaticClass(), GetTransform());
		CurrentPickup->OnPickedUp.BindUObject(this, & ASpawnMuro::PickupCollected);
	}
}


