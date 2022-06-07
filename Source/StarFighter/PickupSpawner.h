// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Pickup.h"
#include "PickupSpawner.generated.h"

UCLASS()
class STARFIGHTER_API APickupSpawner : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APickupSpawner();

	UPROPERTY()
		USceneComponent* SpawnLocation;

	UFUNCTION()
		virtual void PickupCollected();

	UFUNCTION()
		virtual void SpawnPickup() ;
	UPROPERTY(VisibleAnywhere, Category = "Main")
	 APickup* CurrentPickup;
	//timer 
	FTimerHandle MyTimer;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	int hora = 0;

};
