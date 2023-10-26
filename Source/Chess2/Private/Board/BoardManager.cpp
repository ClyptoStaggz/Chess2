// Fill out your copyright notice in the Description page of Project Settings.


#include "Board/BoardManager.h"
#include "Chess2/DebugMacros.h"

// Sets default values
ABoardManager::ABoardManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

int ABoardManager::InitializeBoardState(int Size, FTransform SpawnLocation)
{
	int count = 0;
	FVector nextLocation = SpawnLocation.GetLocation();

	for (auto& string : BoardInfo.Row)
	{
		BoardInfo.InitialLocations.Add(BoardInfo.Row[count], nextLocation);
		count++;


		nextLocation.X += BoardInfo.SpaceOffset;
	}
	return count;
}

void ABoardManager::SpawnBoardOfSize(int Size, FTransform SpawnLocation)
{
	int currentSize = 0;
	FTransform SpawnTransform = SpawnLocation;
	
	int rows = InitializeBoardState(Size, SpawnLocation);
	if (rows != Size)
		return;

	for (int i = 0; i < rows; ++i)
	{
		if (ABoardSpace* resultSpace = SpawnSingleSpace(SpawnTransform))
		{
			CurrentSpace = resultSpace;
			resultSpace->Init(BoardInfo.Row[i], currentSize+1, resultSpace->SpaceInfo.IsWhite);
			resultSpace->BlueprintInit();
			BoardSpaces.Add(resultSpace);
			currentSize++;
		}
		else
		{
			PRINT_STRING_RED("Failed to spawn initial")
				return;
		}
		while (currentSize < Size)
		{
			FVector newSpawnLocation;
			bool isWhite = false;
			ComputeNextSpawnLocation(CurrentSpace, newSpawnLocation, isWhite);

			if (ABoardSpace* resultSpace = SpawnSpaceBegin(newSpawnLocation, isWhite))
			{
				currentSize++;
			}
			else
			{
				PRINT_STRING_RED("Failed to spawn initial")
					return;
			}
		}
	}
}

ABoardSpace* ABoardManager::SpawnSpaceBegin(FVector location, bool isWhite)
{


	FTransform SpawnTransform{ FRotator(0.f, 0.f, 0.f), location, FVector(1.f, 1.f, 1.f) };


	if (ABoardSpace* resultSpace = SpawnSingleSpace(SpawnTransform))
	{
		CurrentSpace = resultSpace;
		resultSpace->Init("A", 1, isWhite);
		BoardSpaces.Add(resultSpace);
		return resultSpace;
	}
	else
	{
		PRINT_STRING_RED("Failed to spawn single")
		return nullptr;
	}
}



/// <summary>
/// Spawns a space at the give Transform
/// </summary>
/// <param name="spawnTransform"></param>
/// <returns>Retuns a pointer to the space or NULL is space failed to spawn</returns>
ABoardSpace* ABoardManager::SpawnSingleSpace(FTransform spawnTransform)
{
	if (ABoardSpace* result = GetWorld()->SpawnActor<ABoardSpace>(BoardSpaceBlueprint, spawnTransform))
		return result;
	else
		PRINT_STRING_RED("Failed to spawn in single")
		return nullptr;
}

void ABoardManager::ComputeNextSpawnLocation(ABoardSpace* switchSpace, FVector& newLocation_out, bool& isWhite_out)
{
	newLocation_out = switchSpace->SpaceInfo.Location + switchSpace->SpaceInfo.SiblingOffset;
	isWhite_out = !switchSpace->SpaceInfo.IsWhite;
	// Log the values to check them
	UE_LOG(LogTemp, Log, TEXT("newLocation_out: %s, isWhite_out: %d"), *newLocation_out.ToString(), isWhite_out);
}


// Called when the game starts or when spawned
void ABoardManager::BeginPlay()
{
	Super::BeginPlay();
	
}


// Called every frame
void ABoardManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

