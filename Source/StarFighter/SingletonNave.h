// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ProyectilEnemigo.h"
#include "SingletonNave.generated.h"


UCLASS()
class STARFIGHTER_API ASingletonNave : public AActor
{
	GENERATED_BODY()
private:
	static ASingletonNave* instance;

	ASingletonNave();
	
public:	
	// Sets default values for this actor's properties
	
	static ASingletonNave* getInstance();

	UPROPERTY()
		AProyectilEnemigo* NaveHija;
	UPROPERTY()
		UStaticMeshComponent* MyMesh;
	UPROPERTY()
		TArray<AProyectilEnemigo*> NaveEA;
	UFUNCTION()
		void SpawnNaves();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	int NNaves;
	float temp;

};
