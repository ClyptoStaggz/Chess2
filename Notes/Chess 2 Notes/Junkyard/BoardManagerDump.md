#dump
#backup
## .h
	/// <summary>
	/// Properties
	/// </summary>
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Board")
		FBoardInfo BoardInfo;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Board")
		int BoardSize;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spaces")
		TArray<ABoardSpace*> BoardSpaces;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spaces")
		FVector StartingSpawnLocation;
	UPROPERTY()
		ABoardSpace* CurrentSpace;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spaces", meta = (DisplayName = "Board Space Blueprint"))
		TSubclassOf<ABoardSpace> BoardSpaceBlueprint;

	/// <summary>
	/// Functions
	/// </summary>
	UFUNCTION(BlueprintCallable, Category = "Spawning")
		void SpawnBoardOfSize(int Size, FTransform SpawnLocation);
	UFUNCTION(BlueprintCallable, Category = "Spawning")
		ABoardSpace* SpawnSpaceBegin(FVector location, bool isWhite);
	UFUNCTION()
		ABoardSpace* SpawnSingleSpace(FTransform spawnTransform);
	UFUNCTION(BlueprintCallable, Category = "Spawning")
		static void ComputeNextSpawnLocation(ABoardSpace* switchSpace, FVector& newLocation, bool& isWhite);




## .cpp
int ABoardManager::InitializeBoardState(int Size, FTransform SpawnLocation)
{
	FTransform workingLocation = SpawnLocation;
	FVector workingOffset;
	int count = 0;
	for (auto& string : BoardInfo.Row)
	{
		//TODO Add logic to change offset for verticle tiles. 
		

		BoardInfo.InitialLocations.Add(BoardInfo.Row[count], workingLocation.GetLocation().X);
		count++;
	}
	return -1;
}

void ABoardManager::SpawnBoardOfSize(int Size, FTransform SpawnLocation)
{
	int currentSize = 0;
	FTransform SpawnTransform = SpawnLocation;
	
	int rows = InitializeBoardState(Size, SpawnLocation);

	for (int i = 0; i < rows; ++i)
	{
		if (ABoardSpace* resultSpace = SpawnSingleSpace(SpawnTransform))
		{
			CurrentSpace = resultSpace;
			resultSpace->Init(BoardInfo.Row[i], currentSize+1, false);
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
