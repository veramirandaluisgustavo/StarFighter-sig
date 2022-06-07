// Fill out your copyright notice in the Description page of Project Settings.


#include "ProyectilE.h"
#include "UObject/ConstructorHelpers.h"
#include "UObject/UObjectBaseUtility.h"
#include "StarFighterGameModeBase.h"
#include "Kismet/GamePlayStatics.h"
#include "Engine/EngineTypes.h"
#include"ProyectilEnemigo.h"
#include "StarFighterGameModeBase.h"




// Sets default values
AProyectilE::AProyectilE()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	MyMove = CreateDefaultSubobject<UMovePE>("MiMovimiento");

	TriggerZone = CreateDefaultSubobject<UBoxComponent>("TriggerZone");

	TriggerZone->SetBoxExtent(FVector(50, 50, 50));
	identificadorP = 0;
	



	My_Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MyMesh"));
	RootComponent = My_Mesh;
	auto MeshAsset = ConstructorHelpers::FObjectFinder<UStaticMesh>(TEXT("/Game/TwinStick/Meshes/TwinStickProjectile.TwinStickProjectile"));
	if (MeshAsset.Object != nullptr)
	{
		My_Mesh->SetStaticMesh(MeshAsset.Object);
	}
	My_Mesh->SetCollisionProfileName(TEXT("OverlapAllDynamic"));
}

void AProyectilE::SetIdentifi(int IDPadre)
{

	identificadorP = IDPadre;

}

// Called when the game starts or when spawned
void AProyectilE::BeginPlay()
{
	Super::BeginPlay();
	
	


	
}

// Called every frame
void AProyectilE::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);




}

void AProyectilE::NotifyActorBeginOverlap(AActor* OtherActor)
{

	PlayerId=OtherActor->GetUniqueID();
	//GEngine->AddOnScreenDebugMessage(-1, 4, FColor::Black, FString::Printf(TEXT("Mi Player es = %i "), PlayerId));

	//GEngine->AddOnScreenDebugMessage(-1, 4, FColor::Red, FString::Printf(TEXT("Mi padre es=%i "),identificadorP ));


	Recarga.ExecuteIfBound();


	UWorld* TheWorld = GetWorld();

	//if (TheWorld != nullptr)
	//{

		AGameModeBase* GameMode = UGameplayStatics::GetGameMode(TheWorld);
		AStarFighterGameModeBase* MyGameMode = Cast<AStarFighterGameModeBase>(GameMode);
		if (MyGameMode != nullptr) {

			MyGameMode->EnemiGetId.ExecuteIfBound(identificadorP,PlayerId);

		}

	//}
}

