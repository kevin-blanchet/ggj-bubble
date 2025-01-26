// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MazeGenerator.generated.h"

class AMazeElement;

UCLASS()
class BUBBLE_API AMazeGenerator : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMazeGenerator();

protected:
	UPROPERTY()
	TArray<AMazeElement*> grid; // Array of MazeElements

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	AMazeElement* GetCell(FIntVector coord);
	FIntVector CoordsFromIndex(int32 index);
	TArray<AMazeElement*> GetValidNeighbours(AMazeElement* cell);

public:	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Size")
	int32 MazeGridSize;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Seed")
	int32 WorldSeed; 
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	TSubclassOf<AMazeElement> MazeElementClass;

	bool bDoesExitExist;

	UFUNCTION(BlueprintCallable, Category = "Maze")
	void GenerateMaze();

	// Create the maze
	void CreateMaze(AMazeElement* previousCell, AMazeElement* currentCell);

};
