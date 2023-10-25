// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BoardSpace.generated.h"

USTRUCT(BlueprintType)
struct FBoardSpaceInfo
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Chess")
		TMap<FString, int> Coordinate;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Chess")
		FVector Location;  // World location of the space

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Chess")
		FVector SiblingOffset;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BasicInfo")
		bool IsWhite;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Chess")
		bool bIsOccupied;
	
	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Chess")
	//	EChessPieceType OccupyingPieceType;

	//UPROPERTY(EditAnywhere, BlueprintReadWrite, CaStegory = "Chess")
	//	AChessPiece* OccupyingPieceReference;  // Reference to the actual chess piece actor

	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Chess")
	//	EBoardHighlight HighlightState;

	// ... Any other properties you might want, like references to potential tracks or special attributes.
};


UCLASS()
class CHESS2_API ABoardSpace : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABoardSpace();

	/// <summary>
	/// Board Details
	/// </summary>
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BasicInfo")
		FBoardSpaceInfo SpaceInfo;


	/// <summary>
	/// Functions
	/// </summary>
	/// <param name="bIsWhite"></param>
	UFUNCTION()
		void Init(FString RowName, int ColumnNumber, bool bIsWhite);
	UFUNCTION(BlueprintImplementableEvent, Category = "Initialization")
		void BlueprintInit();



protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


private:
	static bool bHasRunOnce;
	static bool bIsSiblingOffsetInitialized;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
