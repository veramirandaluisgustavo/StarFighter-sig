// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "movercubo.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class STARFIGHTER_API Umovercubo : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	Umovercubo();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	UPROPERTY(EditAnywhere)
		float velocidad=5.0 ;
	UPROPERTY(EditAnywhere)
		double Limitex1=900 ;
	UPROPERTY(EditAnywhere)
		double Limitex2 =-900;
	UPROPERTY(EditAnywhere)
	float direccion = 2.0f;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	
public:

	AActor* cubo;
	UPROPERTY(EditAnywhere)
		FVector posiciones ;
	float* p_velocidad = & velocidad;
	void SetVelocidad(float _velocidad);
	float GetVelocidad();
	int RandMax=10;
	int RandMin=1;
	int Numrand(int, int);
	float TiempoE;
	bool Destructordistacia;
	
	float tiempodes;
};
