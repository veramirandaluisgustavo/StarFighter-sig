// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/BoxComponent.h"
#include "movercubo.h"
#include "NaveAereaJugador.h"
#include "Math/Vector.h"
#include "GameFramework/RotatingMovementComponent.h"
#include "Pickup.generated.h"


DECLARE_DELEGATE(FPickedupEventSignature)
UCLASS()
class STARFIGHTER_API APickup : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APickup();

	
	UPROPERTY()
		class ANaveAereaJugador* NaveJugador;

	UPROPERTY()
		UBoxComponent* TriggerZone;
	UFUNCTION()
		
	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;
	//UFUNCTION()
	//virtual void NotifyActorEndOverlap(AActor* OtherActor) override;
	UPROPERTY()
		UStaticMeshComponent* MyMesh;
	//movimiento de rotacion
	UPROPERTY()
		URotatingMovementComponent* RotatingComponent;

	FPickedupEventSignature OnPickedUp;



	UPROPERTY(EditAnywhere)
		FString llave= "salud";
	UPROPERTY(EditAnywhere)
		int valor = 1;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(VisibleAnywhere)
		class Umovercubo* movercuboComponent;

	FTimerHandle TimerHandle;

	void UpgradePlayerLevel();

	int NumR;

};
