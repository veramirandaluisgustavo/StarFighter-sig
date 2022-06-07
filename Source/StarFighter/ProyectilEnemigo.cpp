// Fill out your copyright notice in the Description page of Project Settings.


#include "ProyectilEnemigo.h"
#include "NaveAereaJugador.h"
#include "Components/SceneComponent.h"
#include "UObject/UObjectBase.h"
#include "StarFighterGameModeBase.h"
#include "Engine/World.h"
#include "Kismet/GamePlayStatics.h"

// Sets default values
AProyectilEnemigo::AProyectilEnemigo()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	
	My_mesh = CreateDefaultSubobject<UStaticMeshComponent>("MYMESH");
	SpawnLocation = CreateDefaultSubobject<USceneComponent>("SpawnLocation");
	MoveRandom = CreateAbstractDefaultSubobject<UMoveP>("MoveAleatorio");

	auto MeshAsset = ConstructorHelpers::FObjectFinder<UStaticMesh>(TEXT("StaticMesh'/Game/Meshes/SM_Pixel_Enemy_1.SM_Pixel_Enemy_1'"));

	if (MeshAsset.Object != nullptr)
	{
		My_mesh->SetStaticMesh(MeshAsset.Object);
	}


	
	RootComponent = SpawnLocation;
	My_mesh->AttachTo(SpawnLocation);
	//MoveRandom->AttachTo(SpawnLocation);

	//My_mesh->SetRelativeTransform(FTransform(FRotator(0, 90, -90)));
	My_mesh->SetRelativeTransform(FTransform(FRotator(0, 90, -90),FVector(-100,0,0)));
	
	Direccionx = 0;
	Direcciony = 0;
	DireccionGrados=0;
	MyID = 0;
	SetActorEnableCollision(false);
	
}


// Called when the game starts or when spawned
void AProyectilEnemigo::BeginPlay()
{
	Super::BeginPlay();
	

	
	MyID = GetUniqueID();


	MiPosi = GetOwner();


	SpawnP_E();
	
	CurrentP_E->SetIdentifi(MyID);

	P_ECollected();



	UWorld* TheWorld = GetWorld();

	//if (TheWorld != nullptr)
	//{

		AGameModeBase* GameMode = UGameplayStatics::GetGameMode(TheWorld);
		AStarFighterGameModeBase* MyGameM = Cast<AStarFighterGameModeBase>(GameMode);
		if (MyGameM != nullptr) {

			MyGameM->MyGetIDRegister.ExecuteIfBound(MyID);
			MyGameM->MyDestructorProyectil.BindUObject(this, &AProyectilEnemigo::P_ECollected);
		}
		//GEngine->AddOnScreenDebugMessage(-1, 17, FColor::Black, FString::Printf(TEXT("comfirmadaso = %i "), 8989));
	//}






	TArray<AActor*>Apuntadores;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ANaveAereaJugador::StaticClass(), Apuntadores);
	if (Apuntadores.Num() != 0) {

		auto apuntador = Cast<ANaveAereaJugador>(Apuntadores[0]);
		MyObjetivo = apuntador->Objetivo.AddUObject(this, &AProyectilEnemigo::ApuntarEnemigo);
		
	};


	
	
	//UGameplayStatics::GetAllActorsOfClass(GetWorld(), ADianaO::StaticClass(), Apuntadores);
	//if (Apuntadores.Num() != 0) {

	//	auto apuntador = Cast<ADianaO>(Apuntadores[0]);
	//	//MyObjetivo = apuntador->Objetivo.AddUObject(this, &AProyectilEnemigo::ApuntarEnemigo);

	//};
	
}

// Called every frame
void AProyectilEnemigo::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	
	My_mesh->SetRelativeTransform(FTransform(FRotator(0, (DireccionGrados*-1)+180, -90), FVector(100,100, 100)));

	//GEngine->AddOnScreenDebugMessage(-1, 4, FColor::Red, FString::Printf(TEXT("%i "), DireccionGrados));

	//elapseseconds += (DeltaTime * 60);
	//if (elapseseconds > 180)
	//{
	//	elapseseconds -= 180;

	//	GEngine->AddOnScreenDebugMessage(-1, 4, FColor::Blue, FString::Printf(TEXT("%f "), DireccionGrados));
	//	//My_mesh->SetRelativeTransform(FTransform(FRotator(0, DireccionGrados, -90), FVector(-100, 0, 0)));

	//}

}

void AProyectilEnemigo::P_ECollected()
{

	GetWorld()->GetTimerManager().SetTimer(MyTimer, this, &AProyectilEnemigo::SpawnP_E, 0.5, false);
	
	
	CurrentP_E->Recarga.Unbind();
	CurrentP_E->Destroy();

}




void AProyectilEnemigo::SpawnP_E()
{
	UWorld* MyWorld = GetWorld();
	if (MyWorld != nullptr)
	{

		

		CurrentP_E = MyWorld->SpawnActor<AProyectilE>(AProyectilE::StaticClass(), GetTransform());
		CurrentP_E->SetIdentifi(MyID);
	
		CurrentP_E->Recarga.BindUObject(this, &AProyectilEnemigo::P_ECollected);
	}
}

void AProyectilEnemigo::ApuntarEnemigo(int a, int b)
{
	float ordenx= SpawnLocation->GetComponentLocation().X;
	float ordeny= SpawnLocation->GetComponentLocation().Y;
	//GEngine->AddOnScreenDebugMessage(-1, 4, FColor::Red, FString::Printf(TEXT("%i = %i"), a, b));
	//GEngine->AddOnScreenDebugMessage(-1, 4, FColor::Red, FString::Printf(TEXT("ordenx =   %f "), ordenx));
	//GEngine->AddOnScreenDebugMessage(-1, 4, FColor::Red, FString::Printf(TEXT("oredeny =  %f "), ordeny));
	float ordenX = a, ordenY = b;
	// int Cx, Cy,direc;
	//float magnitud;
	//direc = FMath::Atan((a - MiPosi->GetActorLocation().X)/(b- MiPosi->GetActorLocation().Y));
	//DireccionGrados = FMath::Atan((a - MiPosi->GetActorLocation().X)/(b- MiPosi->GetActorLocation().Y));

	//DireccionGrados = FMath::Atan((a - SpawnLocation->GetComponentLocation().X) / (b - SpawnLocation->GetComponentLocation().Y));
	DireccionGrados =(FMath::Atan2((ordenX-ordenx),(ordenY-ordeny))) * 180 / 3.1415;



	
}





