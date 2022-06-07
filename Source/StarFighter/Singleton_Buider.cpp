// Fill out your copyright notice in the Description page of Project Settings.


#include "Singleton_Buider.h"

// Sets default values
ASingleton_Buider::ASingleton_Buider()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ASingleton_Buider::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASingleton_Buider::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

