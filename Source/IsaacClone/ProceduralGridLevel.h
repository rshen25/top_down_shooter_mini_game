// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Room.h"
#include "BasicRoom.h"
#include "BigRoomA.h"
#include "BigRoomB.h"
#include "BigRoomC.h"
#include "BigRoomD.h"
#include "EmptyRoom.h"
#include "MainCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/PlayerStart.h"
#include "Engine/World.h"
#include "GameFramework/Actor.h"
#include "ProceduralGridLevel.generated.h"


enum class ERoomType : uint8 {
	ERoom_Empty,
	ERoom_Basic,
	ERoom_BigA,
	ERoom_BigB,
	ERoom_BigC,
	ERoom_BigD,
	ERoom_BossRoom,
	ERoom_ItemRoom,
	ERoom_Available
};

struct FCoords {
	uint8 Row;
	uint8 Col;
};

UCLASS()
class ISAACCLONE_API AProceduralGridLevel : public AActor
{
	GENERATED_BODY()
	
public:
	static const uint8 LEVEL_SIZE = 10;

	float BIG_ROOM_RATE = 0.8f;

	// static const uint8 AVAIL_ROOM = 100;

	uint8 Floor;

	TArray<FCoords*> FCoordsAvailableRooms = TArray<FCoords*>();

	UPROPERTY(EditAnywhere)
	TSubclassOf<ARoom> SpawnEmptyRoom;

	UPROPERTY(EditAnywhere)
	TSubclassOf<ABasicRoom> SpawnBasicRoom;

	UPROPERTY(EditAnywhere)
	TSubclassOf<ABigRoomA> SpawnBigRoomA;

	UPROPERTY(EditAnywhere)
	TSubclassOf<ABigRoomB> SpawnBigRoomB;

	UPROPERTY(EditAnywhere)
	TSubclassOf<ABigRoomC> SpawnBigRoomC;

	UPROPERTY(EditAnywhere)
	TSubclassOf<ABigRoomD> SpawnBigRoomD;

	UPROPERTY(EditAnywhere)
	TSubclassOf<ABigRoomD> SpawnBigRoom;


public:	
	// Sets default values for this actor's properties
	AProceduralGridLevel();

protected:
	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Rooms)
	//UInstancedStaticMeshComponent* UEmptyRoom;

	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Rooms)
	//UInstancedStaticMeshComponent* UBasicRoom;

	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Rooms)
	//UInstancedStaticMeshComponent* UBigRoomA;

	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Rooms)
	//UInstancedStaticMeshComponent* UBigRoomB;

	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Rooms)
	//UInstancedStaticMeshComponent* UBigRoomC;

	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Rooms)
	//UInstancedStaticMeshComponent* UBigRoomD;

	// The level grid
	uint8 Level[LEVEL_SIZE][LEVEL_SIZE ];

	// LevelGenerator levelGenerator;

	uint8 NumberOfRooms = 18;

	FVector FStartingSpawn;
	FCoords FStartingCoords;

	static const uint32 ROOM_DIMENSION_Y = 2300;
	static const uint32 ROOM_DIMENSION_X = 1700;

	// uint8 Floor;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Spawns the rooms for the level - called by SpawnLevel
	void SpawnRoom(ERoomType RoomType, uint32 X, uint32 Y);

	// Spawns the entire level
	void SpawnLevel();

public:
	// Set the base number of rooms for the level
	void SetNumberOfRooms(uint8 rooms);

	// Get the base number of rooms for the level
	uint8 GetNumberOfRooms();

	// Main function to create a procedural level
	void CreateRandomLevel();

	// Gets the address of the level grid
	uint8* GetLevelGrid();

	FVector GetStartingSpawnCoords();

	void printGrid();

protected:
	// Randomly picks the starting room
	void CreateInitialRoom();

	// Checks and sets the rooms adjacent to the given coordinates in the level grid to available
	void SetRoomsToAvailable(uint8 xPos, uint8 yPos);

	// Adds each room adjacent to the room given in the coordinates to the availability queue
	void AddAvailableRoomToQueue(uint8 xPos, uint8 yPos);

	// Checks if there is room for a Big Room given the coordinates within the level grid
	bool CheckIfAbleToPlaceBigRoom(uint8 xPos, uint8 yPos);

	// Goes through the entire list of available rooms and makes sure that they are actually available
	void refreshAvailableRooms();

	// Adds the boss room furthest away from the starting room via BFS
	void AddBossRoom(FCoords StartingRoom);

	// void BFSHelper(TArray<FCoords*> (*Queue), uint8 (*Distance)[LEVEL_SIZE][LEVEL_SIZE]);

	// Adds an item room to the level
	void AddItemRoom();

	// Adds the door to each room
	void AddDoorsToRoom(uint32 X, uint32 Y, ARoom* Room);
};