// Fill out your copyright notice in the Description page of Project Settings.


#include "DataB.h"
#include "StarFighterGameModeBase.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ADataB::ADataB()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	IDPlayer = 0;
	AsigName = 0;

	NombresE.Add ("Marcos");
	NombresE.Add("Lucas");
	NombresE.Add("Juan");
	NombresE.Add("Pedro");
	NombresE.Add("Jorge");
	NombresE.Add("kevin");
	NombresE.Add("Moises");
	NombresE.Add("Alejandro");

	NombresEP = NombresE.GetData();
}


// Called when the game starts or when spawned
void ADataB::BeginPlay()
{
	Super::BeginPlay();

	
	UWorld* TheWorld = GetWorld();

	if (TheWorld != nullptr)
	{

		AGameModeBase* GameMode = UGameplayStatics::GetGameMode(TheWorld);
		AStarFighterGameModeBase* MyGameMode = Cast<AStarFighterGameModeBase>(GameMode);
		if (MyGameMode != nullptr) {

			MyGameMode->MyGetID.BindUObject(this,&ADataB::DataIdPlayer);
			MyGameMode->EnemiGetId.BindUObject(this, &ADataB::DataIdE);
			MyGameMode->MyGetIDRegister.BindUObject(this, &ADataB::RegistroE);

		}

	}

	FTimerHandle PuntosEnemigoTime;
	GetWorldTimerManager().SetTimer(PuntosEnemigoTime, this, &ADataB::PuntosEnemigosTotales, 20);
}

void ADataB::RegistroE(int Id)
{

	//GEngine->AddOnScreenDebugMessage(-1, 17, FColor::Black, FString::Printf(TEXT("Resgintro real === %i  "), Id));
	bool registradoR= NombresM.Contains(Id);
	
	if (!registradoR)
	{
		if (AsigName <9) {

			NombresM.Add(Id, NombresEP[AsigName]);
			PuntosE.Add(NombresEP[AsigName], 0);

			//GEngine->AddOnScreenDebugMessage(-1, 17, FColor::Black, FString::Printf(TEXT("registrado = %i "),PuntosE[*NombresEP[AsigName]]));
			AsigName += 1;

		}

		
	}
	
}

void ADataB::PuntosEnemigosTotales()
{
	for (int i=0; i < AsigName; i++) {


		GEngine->AddOnScreenDebugMessage(-1, 12, FColor::Green, FString::Printf(TEXT("La nave de %s tiene %i puntos puntos totales"), *NombresEP[i],PuntosE[*NombresEP[i]]));

	}


	
	


}

// Called every frame
void ADataB::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime); 

}

void ADataB::DataIdPlayer(int Id)
{

	

	IDPlayer = Id;
	//GEngine->AddOnScreenDebugMessage(-1, 17, FColor::Black, FString::Printf(TEXT("comfirmadaso = %i "), IDPlayer));

}

void ADataB::DataIdE(int NaveEneId, int JugadorId)
{
	FString templlave;
	int temppuntos=0;


	//GEngine->AddOnScreenDebugMessage(-1, 15, FColor::Black, FString::Printf(TEXT("Player= %i "), IDPlayer));
	//GEngine->AddOnScreenDebugMessage(-1, 6, FColor::Purple, FString::Printf(TEXT("OverlapOthre= %i "), JugadorId));
	if (IDPlayer == JugadorId) {

		templlave = NombresM[NaveEneId];
		temppuntos = PuntosE[templlave]+1;
		PuntosE.Add(templlave, temppuntos);
		GEngine->AddOnScreenDebugMessage(-1, 4, FColor::Black, FString::Printf(TEXT("La nave de %s tiene %i puntos"),*templlave ,temppuntos));

	}

}
	
