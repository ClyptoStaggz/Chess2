// Fill out your copyright notice in the Description page of Project Settings.


#include "Board/BoardSpace.h"

// Sets default values
ABoardSpace::ABoardSpace()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}


void ABoardSpace::Init(FString RowName, int ColumnNumber, bool bIsWhite)
{

	SpaceInfo.Coordinate.Add(RowName, ColumnNumber);
	FVector CurrentLocation = GetActorLocation();
	SpaceInfo.Location = CurrentLocation;



	SpaceInfo.IsWhite = bIsWhite;
	BlueprintInit();
}




// Called when the game starts or when spawned
void ABoardSpace::BeginPlay()
{
	Super::BeginPlay();


	
}

// Called every frame
void ABoardSpace::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

