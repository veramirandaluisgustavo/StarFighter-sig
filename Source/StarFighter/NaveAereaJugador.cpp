// Fill out your copyright notice in the Description page of Project Settings.


#include "NaveAereaJugador.h"
#include "Proyectil.h"
#include "StarFighterGameModeBase.h"
#include "Camera/CameraComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Kismet/GameplayStatics.h"
#include "UObject/UObjectBase.h"

#include <string>
#include <iterator>

#include "Engine/World.h"


ANaveAereaJugador::ANaveAereaJugador()
{
	// Create a camera boom...
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->SetUsingAbsoluteRotation(true); // Don't want arm to rotate when ship does
	CameraBoom->TargetArmLength = 1200.f;
	CameraBoom->SetRelativeRotation(FRotator(-80.f, 0.f, 0.f));
	CameraBoom->bDoCollisionTest = false; // Don't want to pull camera in when it collides with level

	// Create a camera...
	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("TopDownCamera"));
	CameraComponent->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	CameraComponent->bUsePawnControlRotation = false;	// Camera does not rotate relative to arm

	ShipInventory = CreateDefaultSubobject<UInventoryComponent>("MyInventory");

	/*elapseseconds = 0;*/

	// Movement
	MoveSpeed = 1000.0f;

	Energy = 100.0f;

	// Weapon
	GunOffset = FVector(90.f, 0.f, 0.f);
	FireRate = 0.1f;
	bCanFire = false;

	FireForwardValue = 1.0f;
	FireRightValue = 0.0f;

	//const FVector MoveDirection = FVector(FireForwardValue, FireRightValue, 0.f).GetClampedToMaxSize(1.0f);

	//const FRotator FireRotation = MoveDirection.Rotation();
	//// Spawn projectile at an offset from this pawn
	//const FVector SpawnLocation = GetActorLocation() + FireRotation.RotateVector(GunOffset);

	//UWorld* const World = GetWorld();
	//if (World != nullptr)
	//{
	//	//FTransform SpawnLocation;
	//	// spawn the projectile
	//	
	//	ColaProyectiles.Push(World->SpawnActor<AProyectil>(SpawnLocation, FireRotation));
	//	ColaProyectiles.Push(World->SpawnActor<AProyectil>(SpawnLocation, FireRotation));
	//	ColaProyectiles.Push(World->SpawnActor<AProyectil>(SpawnLocation, FireRotation));
	//	ColaProyectiles.Push(World->SpawnActor<AProyectil>(SpawnLocation, FireRotation));
	//	ColaProyectiles.Push(World->SpawnActor<AProyectil>(SpawnLocation, FireRotation));

	//	//UE_LOG(LogTemp, Warning, TEXT("SpawnLocation(X, Y) = %s, %s FireRotation(X, Y) =  s, s"), SpawnLocation.X, SpawnLocation.Y);
	//	//UE_LOG(LogTemp, Warning, TEXT("World not nullptr"));
	//}

	Ejex = 0;
	Ejey = 0;
	


	InfoNave.Add("vida",0);
	InfoNave.Add("salud", 0);
	InfoNave.Add("velocidad", 0);
	InfoNave.Add("mina",0);


}

void ANaveAereaJugador::BeginPlay()
{
	Super::BeginPlay();
	
	NaveJ = GetOwner();

	PlayerID = GetUniqueID();
	
	UWorld* TheWorld = GetWorld();

	if (TheWorld != nullptr)
	{

		AGameModeBase* GameMode = UGameplayStatics::GetGameMode(TheWorld);
		AStarFighterGameModeBase* MyGameMode = Cast<AStarFighterGameModeBase>(GameMode);
		if(MyGameMode!=nullptr){
		
			MyGameMode->MyInventoryDelegate.BindUObject(this, &ANaveAereaJugador::CapsuleNave);

			MyGameMode->MyGetID.ExecuteIfBound(PlayerID);

		}

	}

	
}



void ANaveAereaJugador::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	check(PlayerInputComponent);

	// set up gameplay key bindings
	PlayerInputComponent->BindAxis(MoveForwardBinding);
	PlayerInputComponent->BindAxis(MoveRightBinding);
	//PlayerInputComponent->BindAction(Fire)
	PlayerInputComponent->BindAction(TEXT("Fire"), IE_Pressed, this, &ANaveAereaJugador::Fire);
	PlayerInputComponent->BindAction(TEXT("DropItem"), EInputEvent::IE_Pressed, this, &ANaveAereaJugador::DropItem);

	/*PlayerInputComponent->BindAction(FireBinding);
	PlayerInputComponent->BindAxis(FireForwardBinding);
	PlayerInputComponent->BindAxis(FireRightBinding);*/
}

void ANaveAereaJugador::Tick(float DeltaSeconds)
{
	
	
	//elapseseconds += (DeltaSeconds * 60);
	//if (elapseseconds > 180)
	//{
	
		//elapseseconds -= 180;
		
	
		
		Ejex = GetWorld()->GetFirstPlayerController()->GetPawn()->GetActorLocation().X;
		Ejey = GetWorld()->GetFirstPlayerController()->GetPawn()->GetActorLocation().Y;
	
		Objetivo.Broadcast(Ejex, Ejey);
	
	//}
	
	//UE_LOG(LogTemp, Warning, TEXT("Location: %s."), *Location.ToString());
	// Find movement direction
	const float ForwardValue = GetInputAxisValue(MoveForwardBinding);
	const float RightValue = GetInputAxisValue(MoveRightBinding);

	if (ForwardValue != 0.0f || RightValue != 0.0f) {

		if (ForwardValue != FireForwardValue) {
			FireForwardValue = ForwardValue;
		}

		if (RightValue != FireRightValue) {
			FireRightValue = RightValue;
		}
	}

	

	// Clamp max size so that (X=1, Y=1) doesn't cause faster movement in diagonal directions
	const FVector MoveDirection = FVector(ForwardValue, RightValue, 0.f).GetClampedToMaxSize(1.0f);

	// Calculate  movement
	const FVector Movement = MoveDirection * MoveSpeed * DeltaSeconds;

	// If non-zero size, move this actor
	if (Movement.SizeSquared() > 0.0f)
	{
		const FRotator NewRotation = Movement.Rotation();
		FHitResult Hit(1.f);
		RootComponent->MoveComponent(Movement, NewRotation, true, &Hit);

		if (Hit.IsValidBlockingHit())
		{
			const FVector Normal2D = Hit.Normal.GetSafeNormal2D();
			const FVector Deflection = FVector::VectorPlaneProject(Movement, Normal2D) * (1.f - Hit.Time);
			RootComponent->MoveComponent(Deflection, NewRotation, true);
		}
	}

}

void ANaveAereaJugador::Fire() {
	bCanFire = true;
	UE_LOG(LogTemp, Warning, TEXT("Se presiono la barra espaciadora"));
	// Create fire direction vector
	
	UE_LOG(LogTemp, Warning, TEXT("FireForwardValue: %f FireRightValue: %f"), FireForwardValue, FireRightValue);
	const FVector FireDirection = FVector(FireForwardValue, FireRightValue, 0.f).GetClampedToMaxSize(1.0f);
	//const FVector FireDirection = GetActorLocation();
	// Try and fire a shot
	FireShot(FireDirection);
}

void ANaveAereaJugador::FireShot(FVector FireDirection)
{
	// If it's ok to fire again
	if (bCanFire == true)
	{
		
		// If we are pressing fire stick in a direction
		//if (FireDirection.SizeSquared() > 0.0f)
		//{
			const FRotator FireRotation = FireDirection.Rotation();
			// Spawn projectile at an offset from this pawn
			const FVector SpawnLocation = GetActorLocation() + FireRotation.RotateVector(GunOffset);

			UWorld* const World = GetWorld();
			if (World != nullptr)
			{
				// spawn the projectile
				World->SpawnActor<AProyectil>(SpawnLocation, FireRotation);
				//UE_LOG(LogTemp, Warning, TEXT("SpawnLocation(X, Y) = %s, %s FireRotation(X, Y) =  s, s"), SpawnLocation.X, SpawnLocation.Y);
				//UE_LOG(LogTemp, Warning, TEXT("World not nullptr"));
			}

			

			//bCanFire = false;
			World->GetTimerManager().SetTimer(TimerHandle_ShotTimerExpired, this, &ANaveAereaJugador::ShotTimerExpired, FireRate);

			// try and play the sound if specified

		/*	if (FireSound != nullptr)
			{
				UGameplayStatics::PlaySoundAtLocation(this, FireSound, GetActorLocation());
			}*/

			bCanFire = false;
		//}
	}
}

void ANaveAereaJugador::ShotTimerExpired()
{
	bCanFire = true;
}



void ANaveAereaJugador::DropItem()
{
	if (ShipInventory->CurrentInventory.Num() == 0)
	{
		return;
	}
	AInventoryActor* Item = ShipInventory->CurrentInventory.Last();
	ShipInventory->RemoveFromInventory(Item);
	//should probably use scaled bounding box
	FVector ItemOrigin;
	FVector ItemBounds;
	Item->GetActorBounds(false, ItemOrigin, ItemBounds);
	FTransform PutDownLocation = GetTransform() + FTransform(RootComponent->GetForwardVector() * ItemBounds.GetMax());
	Item->PutDown(PutDownLocation);
}

void ANaveAereaJugador::TakeItem(AInventoryActor* InventoryItem)
{
	InventoryItem->PickUp();
	ShipInventory->AddToInventory(InventoryItem);
}

void ANaveAereaJugador::ShowInventory()
{


	for (auto& Elem : InfoNave)
	{
		//FPlatformMisc::LocalPrint(*FString::Printf(TEXT("(%d, \"%s\")\n"),Elem.Key,*Elem.Value));


		GEngine->AddOnScreenDebugMessage(-1, 1, FColor::Red, FString::Printf(TEXT("%s=%d"), *Elem.Key, Elem.Value));
	}

}

void ANaveAereaJugador::NotifyHit(class UPrimitiveComponent* MyComp, AActor* Other, class UPrimitiveComponent* OtherComp, bool bSelfMoved, FVector HitLocation, FVector HitNormal, FVector NormalImpulse, const FHitResult& Hit)
{
	AInventoryActor* InventoryItem = Cast<AInventoryActor>(Other);
	if (InventoryItem != nullptr)
	{
		TakeItem(InventoryItem);

		


		
	}
}

void ANaveAereaJugador::pruevafuncion(FString dato)
{

	//GEngine->AddOnScreenDebugMessage(-1, 4, FColor::Red, FString::Printf(TEXT("%s "), *dato));

}

int ANaveAereaJugador::GetIdPlayer()
{
	return GetUniqueID();
}

void ANaveAereaJugador::CapsuleNave(FString llave, int valor)
{

	int temp = InfoNave[llave]+valor;

	InfoNave.Add(llave,temp);



	//GEngine->AddOnScreenDebugMessage(-1, 4, FColor::Red, TEXT("vida="));
	GEngine->AddOnScreenDebugMessage(-1, 4, FColor::Red, FString::Printf(TEXT("%s = %i"),*llave,temp));

}

