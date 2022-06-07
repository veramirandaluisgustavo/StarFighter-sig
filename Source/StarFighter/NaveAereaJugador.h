// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "NaveAerea.h"
//#include "Cola.h"
#include "InventoryComponent.h"
#include "NaveAereaJugador.generated.h"

/**
 * 
 */

//class AProyectil;
DECLARE_MULTICAST_DELEGATE_TwoParams(FObjetivo,int,int)
UCLASS()
class STARFIGHTER_API ANaveAereaJugador : public ANaveAerea
{public:
	GENERATED_BODY()

		
	UPROPERTY()
		int Ejex;
	UPROPERTY()
		int Ejey;

		UPROPERTY()
		TMap <FString, int>InfoNave;


		

	UFUNCTION()
		void CapsuleNave(FString llave,int valor);
	
	/** The camera */
	UPROPERTY(Category = Camera, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* CameraComponent;

	/** Camera boom positioning the camera above the character */
	UPROPERTY(Category = Camera, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		class USpringArmComponent* CameraBoom;

	//Cola<class AProyectil*> ColaProyectiles;

public:
	ANaveAereaJugador();


	AActor* NaveJ;
	FObjetivo Objetivo;
	
	// Begin Actor Interface
	virtual void Tick(float DeltaSeconds) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;
	// End Actor Interface

	void Fire();
	
	/* Fire a shot in the specified direction */
	void FireShot(FVector FireDirection);

	/* Handler for the fire timer expiry */
	void ShotTimerExpired();


	virtual void BeginPlay() override;

	/** Offset from the ships location to spawn projectiles */
	UPROPERTY(Category = Gameplay, EditAnywhere, BlueprintReadWrite)
		FVector GunOffset;

	/* How fast the weapon will fire */
	UPROPERTY(Category = Gameplay, EditAnywhere, BlueprintReadWrite)
		float FireRate;

	//Inventario
	UPROPERTY()
		UInventoryComponent* ShipInventory;

	UFUNCTION()
		void TakeItem(AInventoryActor* InventoryItem);

	UFUNCTION()
		void DropItem();


	UFUNCTION()
		void ShowInventory();

	UFUNCTION()
		virtual void NotifyHit(class UPrimitiveComponent* MyComp, AActor* Other, class UPrimitiveComponent* OtherComp, bool bSelfMoved, FVector HitLocation, FVector HitNormal, FVector NormalImpulse, const FHitResult& Hit) override;



	/** Returns CameraComponent subobject **/
	FORCEINLINE class UCameraComponent* GetCameraComponent() const { return CameraComponent; }
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }



	UFUNCTION()

		void pruevafuncion(FString dato);

private:

	/* Flag to control firing  */
	uint32 bCanFire : 1;

	/** Handle for efficient management of ShotTimerExpired timer */
	FTimerHandle TimerHandle_ShotTimerExpired;

	float FireForwardValue;
	float FireRightValue;
	int salud;
	float elapseseconds;

	int PlayerID;


	int GetIdPlayer();

};
