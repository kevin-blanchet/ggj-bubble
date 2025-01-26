// Fill out your copyright notice in the Description page of Project Settings.


#include "MazeGenerator.h"
#include "MazeElement.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AMazeGenerator::AMazeGenerator()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	MazeGridSize = 3;
	WorldSeed = 0;
	bDoesExitExist = false;
}

// Called when the game starts or when spawned
void AMazeGenerator::BeginPlay()
{
	Super::BeginPlay();
}

void AMazeGenerator::GenerateMaze() {

	float alpha = FMath::Min(WorldSeed / 500.f, 1.f);
	float difficulty = alpha * alpha * alpha; // cubic lerp
	difficulty = alpha * alpha; // quadratic lerp
	difficulty = alpha;
	MazeGridSize = FMath::CeilToInt(2 + difficulty * 8.f);

	grid.SetNum(MazeGridSize * MazeGridSize * MazeGridSize);

	// foreach grid element set coord to index
	for (int32 i = 0; i < grid.Num(); i++)
	{
		grid[i] = GetWorld()->SpawnActor<AMazeElement>(MazeElementClass);
		grid[i]->Coord = CoordsFromIndex(i);
	}

	CreateMaze(nullptr, grid[0]);

	// foreach grid element, call UpdateWalls
	for (int32 i = 0; i < grid.Num(); i++)
	{
		grid[i]->UpdateWalls();
	}
}

// Create the maze recursively
AMazeElement* AMazeGenerator::GetCell(FIntVector coord)
{
	if (coord.X < 0 || coord.X >= MazeGridSize || coord.Y < 0 || coord.Y >= MazeGridSize || coord.Z < 0 || coord.Z >= MazeGridSize)
	{
		return nullptr;
	}
	return grid[coord.X + coord.Y * MazeGridSize + coord.Z * MazeGridSize * MazeGridSize];
}

FIntVector AMazeGenerator::CoordsFromIndex(int32 index)
{
	FIntVector coords;
	coords.X = index % MazeGridSize;
	coords.Y = (index / MazeGridSize) % MazeGridSize;
	coords.Z = index / (MazeGridSize * MazeGridSize);
	return coords;
}

void AMazeGenerator::CreateMaze(AMazeElement* previousCell, AMazeElement* currentCell)
{
	FIntVector previousDirection = FIntVector(0, 0, 0);
	if (previousCell != nullptr)
	{
		previousCell->bVisited = true;

		// Get the direction of the current cell
		FIntVector direction = currentCell->Coord - previousCell->Coord;

		// Remove the wall between the two cells
		if (direction.Y == 1)
		{
			previousCell->bRightWall = false;
			currentCell->bLeftWall = false;
		}
		else if (direction.Y == -1)
		{
			previousCell->bLeftWall = false;
			currentCell->bRightWall = false;
		}
		else if (direction.Z == 1)
		{
			previousCell->bTopWall = false;
			currentCell->bBottomWall = false;
		}
		else if (direction.Z == -1)
		{
			previousCell->bBottomWall = false;
			currentCell->bTopWall = false;
		}
		else if (direction.X == 1)
		{
			previousCell->bFrontWall = false;
			currentCell->bBackWall = false;
		}
		else if (direction.X == -1)
		{
			previousCell->bBackWall = false;
			currentCell->bFrontWall = false;
		}

		previousDirection = direction;
	}

	currentCell->bVisited = true;
	AMazeElement* nextCell;
	int32 numberOfNeighbours = 0;

	do {
		// Get the neighbours of the current cell
		TArray<AMazeElement*> neighbours = GetValidNeighbours(currentCell);

		// If there are no neighbours, return
		numberOfNeighbours = neighbours.Num();

		if (numberOfNeighbours != 0) {
			// Get a random neighbour
			int32 randomIndex = FMath::RandRange(0, neighbours.Num() - 1);
			nextCell = neighbours[randomIndex];

			// Recursively create the maze
			CreateMaze(currentCell, nextCell);
		}
		else {
			if (!bDoesExitExist) {
				// Set the exit
				currentCell->bIsExit = true;
				bDoesExitExist = true;
			}
		}
	} while (numberOfNeighbours != 0);
}

// Get neighbours of a cell
TArray<AMazeElement*> AMazeGenerator::GetValidNeighbours(AMazeElement* cell)
{
	TArray<AMazeElement*> neighbours;
	FIntVector coord = cell->Coord;
	for (int32 i = 0; i < 6; i++)
	{
		FIntVector direction;
		switch (i)
		{
		case 0: direction = FIntVector(1, 0, 0); break;
		case 1: direction = FIntVector(-1, 0, 0); break;
		case 2: direction = FIntVector(0, 1, 0); break;
		case 3: direction = FIntVector(0, -1, 0); break;
		case 4: direction = FIntVector(0, 0, 1); break;
		case 5: direction = FIntVector(0, 0, -1); break;
		}
		AMazeElement* neighbour = GetCell(coord + direction);
		if (neighbour != nullptr && !neighbour->bVisited)
		{
			neighbours.Add(neighbour);
		}
	}
	return neighbours;
}