// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ProyectilE.h" 
#include "MoveP.h"
#include "ProyectilEnemigo.generated.h"


UCLASS()
class STARFIGHTER_API AProyectilEnemigo : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AProyectilEnemigo();


	UPROPERTY()
		int MyID;


	AActor* MiPosi;

	UPROPERTY()
		USceneComponent* SpawnLocation;
	UPROPERTY()
		UStaticMeshComponent* My_mesh;

	UFUNCTION()
		virtual void P_ECollected();

	UFUNCTION()
		virtual void SpawnP_E();

	UPROPERTY()
		//APickup* CurrentP_E;
		AProyectilE* CurrentP_E;
	UFUNCTION()
		void ApuntarEnemigo(int a, int b);

	//timer 
	FTimerHandle MyTimer;


	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	FDelegateHandle MyObjetivo;
	float DireccionGrados ;
	float Direccionx=0, Direcciony=0;
	float magnitud;
	float Cx, Cy;



	float elapseseconds=0;

	UMoveP* MoveRandom;

};
