// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MazeElement.generated.h"

UCLASS()
class BUBBLE_API AMazeElement : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMazeElement();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
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

	FIntVector Coord;

	UPROPERTY()
	bool bVisited;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintImplementableEvent)
	void UpdateWalls();

};
