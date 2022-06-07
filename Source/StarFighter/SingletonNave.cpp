// Fill out your copyright notice in the Description page of Project Settings.


#include "SingletonNave.h"
#include "Kismet/GamePlayStatics.h"

// Sets default values

ASingletonNave* ASingletonNave::instance = 0;

ASingletonNave::ASingletonNave()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	MyMesh = CreateDefaultSubobject<UStaticMeshComponent>("MYMESH");
	auto MeshAsset = ConstructorHelpers::FObjectFinder<UStaticMesh>(TEXT("StaticMesh'/Game/Meshes/SM_Pixel_Enemy_1.SM_Pixel_Enemy_1'"));
	

	if (MeshAsset.Object != nullptr)
	{
		MyMesh->SetStaticMesh(MeshAsset.Object);
	}
	RootComponent = MyMesh;
	//this->SetActorTransform(FTransform(FRotator(0, 90, -90)));
	NNaves = 0;
	temp = 0;
}

ASingletonNave* ASingletonNave::getInstance()
{
	if (instance == 0)
	{
		instance = NewObject <ASingletonNave>();
	}

	return instance;
}

void ASingletonNave::SpawnNaves()
{

	


		UWorld* MyWorld = GetWorld();
	//if (MyWorld != nullptr)
	//{



		NaveEA.Add(MyWorld->SpawnActor<AProyectilEnemigo>(AProyectilEnemigo::StaticClass(), GetTransform()))  ;
		NaveEA[NNaves]->SetActorScale3D(FVector(1,1,1));
		//NaveEA[NNaves]->SetActorTransform(FTransform(FRotator(0, 90, -90),FVector(10,10,10)));
		NNaves++;
		
	//}


}

// Called when the game starts or when spawned
void ASingletonNave::BeginPlay()
{
	Super::BeginPlay();
	this->SetActorScale3D(FVector(2, 2, 2));
	temp = GetWorld()->GetRealTimeSeconds();

	
}

// Called every frame
void ASingletonNave::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (GetWorld()->GetRealTimeSeconds() - temp > 3.0f) {

		temp = GetWorld()->GetRealTimeSeconds();

		if (NaveEA.Num() < 6) {

			SpawnNaves();

		}


	}
	


}

