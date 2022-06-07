// Fill out your copyright notice in the Description page of Project Settings.


#include "Pickup.h" 
#include <sstream>
#include<string>
#include <iostream>
#include "movercubo.h"
#include "StarFighterGameModeBase.h"
#include "Kismet/GameplayStatics.h"
#include "UObject/ConstructorHelpers.h"

// Sets default values
APickup::APickup()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;


	movercuboComponent = CreateDefaultSubobject<Umovercubo>(TEXT("HealthManaComponent"));

	TriggerZone = CreateDefaultSubobject<UBoxComponent>("TriggerZone");

	TriggerZone->SetBoxExtent(FVector(50, 50, 50));

	MyMesh = CreateDefaultSubobject<UStaticMeshComponent>("MyMesh");

	RotatingComponent = CreateDefaultSubobject<URotatingMovementComponent>("RotatingComponent");
	RootComponent = MyMesh;

	auto MeshAsset = ConstructorHelpers::FObjectFinder<UStaticMesh>(TEXT("StaticMesh'/Engine/BasicShapes/Cylinder.Cylinder'"));

	if (MeshAsset.Object != nullptr)
	{
		MyMesh->SetStaticMesh(MeshAsset.Object);
	}

	MyMesh->SetCollisionProfileName(TEXT("OverlapAllDynamic"));
	RotatingComponent->RotationRate = FRotator(15, 0, 15);

	NumR= FMath::RandRange(1, 4);
	switch (NumR)
	{

	case 1:llave = "salud"; break;
	case 2:llave= "vida"; break;
	case 3:llave = "velocidad"; break;
	case 4:llave = "mina"; break;
	default:llave = "salud";
		break;
	}


}

void APickup::NotifyActorBeginOverlap(AActor* OtherActor)
{

	

	OnPickedUp.ExecuteIfBound();
	
	//string String = static_cast<ostringstream*>(&(ostringstream() << vel))->str();



	auto Message = FString::Printf(TEXT("%s me disparo  "), *(OtherActor->GetName()));



	//auto Message2 = FString::Printf(TEXT("%s la velocidad es "),*());
	//GEngine->AddOnScreenDebugMessage(-1, 10, FColor::Red, Message);
	//GEngine->AddOnScreenDebugMessage(-1, 10, FColor::Red, Message2);


	UWorld* TheWorld = GetWorld();

	if (TheWorld != nullptr)
	{

		AGameModeBase* GameMode = UGameplayStatics::GetGameMode(TheWorld);
		AStarFighterGameModeBase* MyGameMode = Cast<AStarFighterGameModeBase>(GameMode);
		if (MyGameMode != nullptr) {

			MyGameMode->MyInventoryDelegate.ExecuteIfBound(llave,valor);

		}

	}
	



}
// Called when the game starts or when spawned
void APickup::BeginPlay()
{
	Super::BeginPlay();

	GetWorldTimerManager().SetTimer(TimerHandle, this,&APickup::UpgradePlayerLevel, 5.f, true);

	
}


void APickup::UpgradePlayerLevel()
{
	
	movercuboComponent->GetVelocidad();
	
}

// Called every frame
void APickup::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

