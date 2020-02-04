// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ProceduralLevel.generated.h"

UCLASS()
class TWINSTICKMINIGAME_API AProceduralLevel : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AProceduralLevel();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// An array of all room positions
	UPROPERTY(Category = Level, EditAnywhere, BlueprintReadWrite)
	TArray<FVector> roomPositions;

	// An array of all the room sizes
	UPROPERTY(Category = Level, EditAnywhere, BlueprintReadWrite)
	TArray<FVector> roomSizes;

	// The size of the level
	UPROPERTY(Category = Level, EditAnywhere, BlueprintReadWrite)
	int32 mazeSize;

	// The maximum number of rooms in a level
	UPROPERTY(Category = Level, EditAnywhere, BlueprintReadWrite)
	int32 maxRooms;

	// The largest size a room can be
	UPROPERTY(Category = Level, EditAnywhere, BlueprintReadWrite)
	int32 maxRoomSize;

	// The smallest size a room can be
	UPROPERTY(Category = Level, EditAnywhere, BlueprintReadWrite)
	int32 minRoomSize;

	// Number of times to try placing a room until we give up
	UPROPERTY(Category = Level, EditAnywhere, BlueprintReadWrite)
	int32 placementTries;

	UPROPERTY(Category = Level, EditAnywhere, BlueprintReadWrite)
	int32 tileSize;

	UPROPERTY(Category = Level, EditAnywhere, BlueprintReadWrite)
	TArray<FVector> roomCorridorStart;

	UPROPERTY(Category = Level, EditAnywhere, BlueprintReadWrite)
	TArray<FVector> roomCorridorEnd;

	UPROPERTY(Category = Level, VisibleAnywhere, BlueprintReadOnly)
	TArray<FVector> centers;

	// Arrays used to hold the corridors that connect each room
	UPROPERTY(Category = Level, VisibleAnywhere, BlueprintReadOnly)
	TArray<FVector> roomStart;

	UPROPERTY(Category = Level, VisibleAnywhere, BlueprintReadOnly)
	TArray<FVector> roomEnd;

	UPROPERTY(Category = Level, VisibleAnywhere, BlueprintReadOnly)
	TArray<FIntVector> edges;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Tries to place a room into the level
	UFUNCTION(Category = Room, BlueprintCallable)
	void GenerateLevel();

	// Calculates the center of each room and returns a FVector of the XY coords of each room, Z coord is the index of the room
	UFUNCTION(Category = Room, BlueprintCallable)
	TArray<FVector> GetCenterOfRooms(const TArray<FVector>& positions, const TArray<FVector>& sizes);

	// Creates a Minimum Spanning Tree for all the rooms in a level. This is used to figure out which rooms are connected by corridors/hallways
	UFUNCTION(Category = Room, BlueprintCallable)
	TArray<FIntVector> CreateMST(TArray<FVector>& rooms);
	
private:
	UInstancedStaticMeshComponent* room;
	UInstancedStaticMeshComponent* corridor;

	UFUNCTION(Category = Room, BlueprintCallable)
	bool IsOverlapping(const FVector pos1, const FVector size1, const FVector pos2, const FVector size2);

	// Generates a randomly sized room and a random position
	UFUNCTION(Category = Room, BlueprintCallable)
	void GenerateRoom(FVector &OUTRoomPosition, FVector &OUTRoomSize);

	// Tries to place a room into the level
	UFUNCTION(Category = Room, BlueprintCallable)
	bool TryToPlaceRoom(FVector& OUTPosition, FVector& OUTSize);

	// Finds the minimal distance between rooms and adds an edge between the two (Prim's Algorithm)
	UFUNCTION(Category = Level, BlueprintCallable)
	FIntVector CreateMSTHelper(const TArray<FVector>& completed, const TArray<FVector>& remaining);

	// Creates a Corridor between rooms that are closest to each other
	UFUNCTION(Category = Level, BlueprintCallable)
	void CreateInitialCorridors(const TArray<FVector>& positions, const TArray<FVector>& sizes);
	
	void CreateJointCorridor(FVector &bPos, FVector &bSize, FVector &aPos, FVector &aSize, int32 aX, int32 aY, int32 bX, int32 bY);

	UFUNCTION(Category = Level, BlueprintCallable)
	void SpawnRooms(const FVector position, const FVector size, UInstancedStaticMeshComponent* room);
	
	UFUNCTION(Category = Level, BlueprintCallable)
	void SpawnCorridor(const FVector& start, const FVector& end, UInstancedStaticMeshComponent* corridor);

	UFUNCTION(Category = Level, BlueprintCallable)
	void SpawnFloor(const float levelSize);
};
