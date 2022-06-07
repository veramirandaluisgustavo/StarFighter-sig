// Fill out your copyright notice in the Description page of Project Settings.


#include "PickupSpawner.h"
#include "StarFighterGameModeBase.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
APickupSpawner::APickupSpawner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;


	//funcion para especificar donde debe aaparecer el actor****
	SpawnLocation = CreateDefaultSubobject<USceneComponent>("SpawnLocation");

}

// Called when the game starts or when spawned
void APickupSpawner::BeginPlay()
{
	Super::BeginPlay();
	
      SpawnPickup();

	  UWorld* TheWorld = GetWorld();
	  if (TheWorld != nullptr)
	  {

		  AGameModeBase* GameMode = UGameplayStatics::GetGameMode(TheWorld);
		  AStarFighterGameModeBase* MyGameMode = Cast<AStarFighterGameModeBase>(GameMode);
		  if (MyGameMode != nullptr) {

			  MyGameMode->MyDestructorDelegate.BindUObject(this, &APickupSpawner::PickupCollected);

		  }

	  }

}

// Called every frame
void APickupSpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


void APickupSpawner::PickupCollected()
{
	GetWorld()->GetTimerManager().SetTimer(MyTimer, this, &APickupSpawner::SpawnPickup, 3, false);

	CurrentPickup->OnPickedUp.Unbind();
	CurrentPickup->Destroy();




}


void APickupSpawner::SpawnPickup()
{
	UWorld* MyWorld = GetWorld();
	if (MyWorld != nullptr)
	{
		CurrentPickup = MyWorld->SpawnActor<APickup>(APickup::StaticClass(), GetTransform());
		CurrentPickup->OnPickedUp.BindUObject(this, &APickupSpawner::PickupCollected);
	}
}

