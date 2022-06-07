// Fill out your copyright notice in the Description page of Project Settings.


#include "MoveP.h"
#include "StarFighterGameModeBase.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/World.h"
// Sets default values for this component's properties
UMoveP::UMoveP()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	Destructordistacia = true;
	// ...
}


// Called when the game starts
void UMoveP::BeginPlay()
{


	Super::BeginPlay();
	TiempoE = GetWorld()->GetRealTimeSeconds();
	cubo = GetOwner();
	// ...
	
}


// Called every frame
void UMoveP::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);


	posiciones.X = velocidad + cubo->GetActorLocation().X;
	posiciones.Y = ejey + cubo->GetActorLocation().Y;
	posiciones.Z = cubo->GetActorLocation().Z;
	cubo->SetActorLocation(posiciones);



	if (GetWorld()->GetRealTimeSeconds() - TiempoE > 1.0f) {

		TiempoE = GetWorld()->GetRealTimeSeconds();
		int numerox = Numrand(1, 10);
		if (numerox > 5) {

			velocidad *= -1;
		}
		int numeroy = Numrand(1, 10);
		if (numeroy > 5) {

			ejey *= -1;
		}

	}


//declarando limites
	if (cubo->GetActorLocation().X > 900 || cubo->GetActorLocation().X < -900)
	{

		velocidad *= -1;
		//cubo->SetActorLocation(FVector(-440, -20, 70));
	}
	if (cubo->GetActorLocation().Y > 1400 || cubo->GetActorLocation().Y < -1100)
	{

		ejey *= -1;
		//cubo->SetActorLocation(FVector(-440, -20, 70));
	}
	
	// ...
}


int UMoveP::Numrand(int min, int max)
{
	return FMath::RandRange(min, max);
}

