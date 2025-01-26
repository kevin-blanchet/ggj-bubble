// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MazeElement.generated.h"

UCLASS(Blueprintable, BlueprintType)
class BUBBLE_API AMazeElement : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMazeElement();

	UPROPERTY(BlueprintReadOnly, Category = "Size")
	bool bLeftWall;
	UPROPERTY(BlueprintReadOnly, Category = "Size")
	bool bRightWall;
	UPROPERTY(BlueprintReadOnly, Category = "Size")
	bool bTopWall;
	UPROPERTY(BlueprintReadOnly, Category = "Size")
	bool bBottomWall;
	UPROPERTY(BlueprintReadOnly, Category = "Size")
	bool bFrontWall;
	UPROPERTY(BlueprintReadOnly, Category = "Size")
	bool bBackWall;

	UPROPERTY(BlueprintReadOnly, Category = "Coordinates")
	FIntVector Coord;

	UPROPERTY(BlueprintReadOnly, Category = "Coordinates")
	bool bIsExit;

	bool bVisited;

	UFUNCTION(BlueprintImplementableEvent)
	void UpdateWalls();
};
