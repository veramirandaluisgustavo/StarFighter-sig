// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DataB.generated.h"

UCLASS()
class STARFIGHTER_API ADataB : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADataB();
	UPROPERTY()
		int IDPlayer;

	UFUNCTION()
		void DataIdPlayer(int Id);
	UFUNCTION()
		void DataIdE(int NaveEneId,int JugadorId);
	UPROPERTY()
	TArray<FString> NombresE;
	UPROPERTY()
	TMap< FString,int> PuntosE;
	UPROPERTY()
		TMap<int,FString> NombresM;
	UPROPERTY()
	int AsigName;

	UFUNCTION()
		void RegistroE(int Id);
	UFUNCTION()
		void PuntosEnemigosTotales();


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	FString* NombresEP;
	
};
