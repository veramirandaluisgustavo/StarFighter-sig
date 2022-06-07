// Fill out your copyright notice in the Description page of Project Settings.


#include "MovePE.h"
#include "StarFighterGameModeBase.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/World.h"


// Sets default values for this component's properties
UMovePE::UMovePE()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	Destructordistacia = true;


	EnemigoX=0, EnemigoY=0;
	tiempodes = 0;

	velocidad = 10;
	ejey = 10;

	// ...
}


// Called when the game starts
void UMovePE::BeginPlay()
{


	Super::BeginPlay();
	TiempoE = GetWorld()->GetRealTimeSeconds();
	cubo = GetOwner();
	CalcularDir();

	//

	velocidad *= EnemigoX;
	ejey *= EnemigoY;


	


	// ...

}


// Called every frame
void UMovePE::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);


	posiciones.X = velocidad + cubo->GetActorLocation().X;
	posiciones.Y = ejey + cubo->GetActorLocation().Y;
	posiciones.Z = cubo->GetActorLocation().Z;
	cubo->SetActorLocation(posiciones);



	if (GetWorld()->GetRealTimeSeconds() - TiempoE > 3.0f) {

		UWorld* TheWorld = GetWorld();
		if (TheWorld != nullptr)
		{

			AGameModeBase* GameMode = UGameplayStatics::GetGameMode(TheWorld);
			AStarFighterGameModeBase* MyGameMode = Cast<AStarFighterGameModeBase>(GameMode);
			if (MyGameMode != nullptr) {

				MyGameMode->MyDestructorProyectil.ExecuteIfBound();

			}

		}

	}


	//declarando limites
	if (cubo->GetActorLocation().X > 900 || cubo->GetActorLocation().X < -900)
	{

		UWorld* TheWorld = GetWorld();
		if (TheWorld != nullptr)
		{

			AGameModeBase* GameMode = UGameplayStatics::GetGameMode(TheWorld);
			AStarFighterGameModeBase* MyGameMode = Cast<AStarFighterGameModeBase>(GameMode);
			if (MyGameMode != nullptr) {

				MyGameMode->MyDestructorProyectil.ExecuteIfBound();

			}

		}
		//cubo->SetActorLocation(FVector(-440, -20, 70));
	}
	if (cubo->GetActorLocation().Y > 1400 || cubo->GetActorLocation().Y < -1100)
	{

		UWorld* TheWorld = GetWorld();
		if (TheWorld != nullptr)
		{

			AGameModeBase* GameMode = UGameplayStatics::GetGameMode(TheWorld);
			AStarFighterGameModeBase* MyGameMode = Cast<AStarFighterGameModeBase>(GameMode);
			if (MyGameMode != nullptr) {

				MyGameMode->MyDestructorProyectil.ExecuteIfBound();

			}

		}
		//cubo->SetActorLocation(FVector(-440, -20, 70));
	}

	// ...
}


int UMovePE::Numrand(int min, int max)
{
	return FMath::RandRange(min, max);
}


void UMovePE::CalcularDir()
{
	float tempx, tempy;
	tempx = (GetWorld()->GetFirstPlayerController()->GetPawn()->GetActorLocation().X) - cubo->GetActorLocation().X;
	tempy = (GetWorld()->GetFirstPlayerController()->GetPawn()->GetActorLocation().Y)-cubo->GetActorLocation().Y;


	if (FMath::Abs(tempx) > FMath::Abs(tempy)) 
	{

		if(tempx>0)
		{
			
			EnemigoX = 1;

			if (tempy > 0)
			{

				EnemigoY = FMath::Abs(tempy / tempx);

			}
			else
			{

				EnemigoY=-1* FMath::Abs(tempy / tempx);

			}
		
		}
		else
		{

			EnemigoX = -1;


			if (tempy > 0)
			{

				EnemigoY = FMath::Abs(tempy / tempx);

			}
			else
			{

				EnemigoY = -1 * FMath::Abs(tempy / tempx);

			}

		}


	}
	else
	{

		if (tempy > 0)
		{

			EnemigoY = 1;

			if (tempx > 0)
			{

				EnemigoX = FMath::Abs(tempx / tempy);

			}
			else
			{

				EnemigoX = -1 * FMath::Abs(tempx / tempy);

			}

		}
		else
		{

			EnemigoY = -1;


			if (tempx > 0)
			{

				EnemigoX = FMath::Abs(tempx / tempy);

			}
			else
			{

				EnemigoX = -1 * FMath::Abs(tempx / tempy);

			}

		}

	}




}

