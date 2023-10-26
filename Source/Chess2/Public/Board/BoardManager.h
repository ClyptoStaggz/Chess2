// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BoardSpace.h"
#include "BoardManager.generated.h"


USTRUCT(BlueprintType)
struct FBoardInfo
{
	GENERATED_BODY()
	/// <summary>
	/// Initializes the rows array. Set in blueprint. ex. A, B, C 
	/// </summary>
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Board Info")
		TArray<FString> Row; 
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Board Info")
		float SpaceOffset;

	/// <summary>
	/// Gives a location to each row 
	/// </summary>
	UPROPERTY()
	TMap<FString, FVector> InitialLocations;
};


UCLASS()
class CHESS2_API ABoardManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABoardManager();

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


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	int InitializeBoardState(int Size, FTransform SpawnLocation);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
