


//#include "DianaO.h"
//
//
//ADianaO::ADianaO()
//{
// 	
//	PrimaryActorTick.bCanEverTick = true;
//	MeshDiana = CreateDefaultSubobject<UStaticMeshComponent>("caraDiana");
//	auto MeshAsset = ConstructorHelpers::FObjectFinder<UStaticMesh>(TEXT("StaticMesh'/Engine/BasicShapes/Cube.Cube'"));
//	if (MeshAsset.Object != nullptr)
//	{
//		MeshDiana->SetStaticMesh(MeshAsset.Object);
//	}
//
//	RootComponent = MeshDiana;
//	Ejex = 0;
//	Ejey = 0;
//	elapseseconds = 0;
//
//}
//
//
//void ADianaO::BeginPlay()
//{
//	Super::BeginPlay();
//	NaveJ = GetOwner();
//}
//
//
//void ADianaO::Tick(float DeltaTime)
//{
//	Super::Tick(DeltaTime);
//
//
//	elapseseconds += (DeltaTime * 60);
//	if (elapseseconds > 180)
//	{
//
//		elapseseconds -= 180;
//
//
//		
//		//Ejex = NaveJ->GetActorLocation().X;
//		//Ejey = NaveJ->GetActorLocation().Y;
//
//		Objetivo.Broadcast(Ejex, Ejey);
//
//	}
//}

