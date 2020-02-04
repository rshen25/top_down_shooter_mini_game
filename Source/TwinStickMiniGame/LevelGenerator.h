// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

//
//enum class ERoomType : uint8 {
//	ERoom_Empty,
//	ERoom_Basic,
//	ERoom_BigA,
//	ERoom_BigB,
//	ERoom_BigC,
//	ERoom_BigD,
//	ERoom_Available
//};
//
//struct FCoords {
//	uint8 X;
//	uint8 Y;
//};

/**
 * 
 */
class TWINSTICKMINIGAME_API LevelGenerator
{
public:
	LevelGenerator();
	//LevelGenerator(uint8 rooms);
	~LevelGenerator();

//public:
//	static const uint8 LEVEL_SIZE = 12;
//
//	// static const uint8 AVAIL_ROOM = 100;
//
//	ERoomType ERoom;
//
//	// The level grid
//	uint8 Level[LEVEL_SIZE][LEVEL_SIZE];
//
//	uint8 NumberOfRooms = 12;
//
//	uint8 Floor;
//
//	TArray<FCoords> FCoordsAvailableRooms = TArray<FCoords>();
//
//public:
//	// Set the base number of rooms for the level
//	void SetNumberOfRooms(uint8 rooms);
//
//	// Get the base number of rooms for the level
//	uint8 GetNumberOfRooms();
//
//	// Main function to create a procedural level
//	void CreateRandomLevel();
//
//	// Gets the address of the level grid
//	uint8* GetLevelGrid();
//
//	void printGrid();
//
//protected:
//	// Randomly picks the starting room
//	void CreateInitialRoom();
//
//	// Checks and sets the rooms adjacent to the given coordinates in the level grid to available
//	void SetRoomsToAvailable(uint8 xPos, uint8 yPos);
//	
//	// Adds each room adjacent to the room given in the coordinates to the availability queue
//	void AddAvailableRoomToQueue(uint8 xPos, uint8 yPos);
//
//	// Checks if there is room for a Big Room given the coordinates within the level grid
//	bool CheckIfAbleToPlaceBigRoom(uint8 xPos, uint8 yPos);
//
//	// Goes through the entire list of available rooms and makes sure that they are actually available
//	void refreshAvailableRooms();
};
