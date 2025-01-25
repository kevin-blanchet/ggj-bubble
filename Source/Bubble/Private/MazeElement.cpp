// Fill out your copyright notice in the Description page of Project Settings.


#include "MazeElement.h"

// Sets default values
AMazeElement::AMazeElement()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	bLeftWall = true;
	bRightWall = true;
	bTopWall = true;
	bBottomWall = true;
	bFrontWall = true;
	bBackWall = true;

	bVisited = false;

	Coord = FIntVector(0, 0, 0);
}

// Called when the game starts or when spawned
void AMazeElement::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMazeElement::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

