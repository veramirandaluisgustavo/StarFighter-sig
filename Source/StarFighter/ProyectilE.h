// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/BoxComponent.h"
#include "MovePE.h"
#include "ProyectilE.generated.h"



DECLARE_DELEGATE(FProyectileE)
UCLASS()
class STARFIGHTER_API AProyectilE : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AProyectilE();
	
	UPROPERTY()
		int identificadorP;

	UPROPERTY()
		UStaticMeshComponent* My_Mesh;
	
		FProyectileE Recarga;

		UBoxComponent* TriggerZone;

		UMovePE* MyMove;

		UFUNCTION()
			void SetIdentifi(int IDPadre);


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;


	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;

	
	
	int PlayerId;

};
