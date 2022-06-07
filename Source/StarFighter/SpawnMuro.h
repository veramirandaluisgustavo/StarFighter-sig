// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MuroMove.h"
#include "GameFramework/Actor.h"
#include "SpawnMuro.generated.h"

UCLASS()
class STARFIGHTER_API ASpawnMuro : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ASpawnMuro();

	UPROPERTY()
		USceneComponent* SpawnLocation;

	UFUNCTION()
		void PickupCollected();

	UFUNCTION()
		void SpawnMuro();
	UPROPERTY()
		AMuroMove* CurrentPickup;
	//timer 
	FTimerHandle MyTimer;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};

