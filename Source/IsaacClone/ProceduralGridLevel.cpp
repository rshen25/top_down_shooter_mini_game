// Fill out your copyright notice in the Description page of Project Settings.

#include "ProceduralGridLevel.h"
#include "IsaacClonePawn.h"

// TODO: make the room doors, do not allow the player to fall to nothing
// Sets default values
AProceduralGridLevel::AProceduralGridLevel()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//NumberOfRooms = FMath::RandRange(18, 21 + (Floor * 2));

	// Create default scene component
	USceneComponent* RootSceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
	RootComponent = RootSceneComponent;

	SpawnEmptyRoom = AEmptyRoom::StaticClass();
	SpawnBasicRoom = ABasicRoom::StaticClass();
	SpawnBigRoomA = ABigRoomA::StaticClass();
	SpawnBigRoomB = ABigRoomB::StaticClass();
	SpawnBigRoomC = ABigRoomC::StaticClass();
	SpawnBigRoomD = ABigRoomD::StaticClass();
}

// Called when the game starts or when spawned
void AProceduralGridLevel::BeginPlay()
{
	Super::BeginPlay();

	// Create random level
	CreateRandomLevel();
	printGrid();
	// levelGenerator.CreateRandomLevel();

	AddBossRoom(FStartingCoords);
	SpawnLevel();
}

// Called every frame
void AProceduralGridLevel::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AProceduralGridLevel::CreateRandomLevel()
{
	uint8 remaining = NumberOfRooms;
	uint8 TmpRoomIndex = 0;
	float RoomType;
	FCoords* tmp = new FCoords();
	// FCoords currentCoords;

	// Create the first room
	CreateInitialRoom();
	remaining--;

	// Create the rest of the rooms for the level
	while (remaining > 0) {
		// Randomly choose an available spot to place a room
		if (FCoordsAvailableRooms.Num() != 0 && FCoordsAvailableRooms.IsValidIndex(0)) {
			TmpRoomIndex = FMath::RandRange(0, FCoordsAvailableRooms.Num() - 1);
			if (TmpRoomIndex > 0 && TmpRoomIndex < FCoordsAvailableRooms.Num()) {
				tmp = FCoordsAvailableRooms[TmpRoomIndex];
			}
		}

		// Randomly choose a type of room
		RoomType = FMath::FRand();
		// Room will be big
		if (RoomType > BIG_ROOM_RATE) {
			// Check if type is a big room and if it is able to be placed and check if all other rooms
			// are able to be placed
			if (CheckIfAbleToPlaceBigRoom(tmp->Row, tmp->Col)) {
				remaining -= 2;
				refreshAvailableRooms();
			}

			// if able, then place them all

		}
		else {
			// Room type is basic
			// Change available room to filled
			Level[tmp->Row][tmp->Col] = (uint8)ERoomType::ERoom_Basic;
			SetRoomsToAvailable(tmp->Row, tmp->Col);

			// UE_LOG(LogTemp, Warning, TEXT("TmpRoomIndex: %d"), TmpRoomIndex);
			// UE_LOG(LogTemp, Warning, TEXT("Number of Available Rooms: %d"), FCoordsAvailableRooms.Num());
			if (TmpRoomIndex >= 0 && TmpRoomIndex < FCoordsAvailableRooms.Num()) {
				FCoordsAvailableRooms.RemoveAt((int32)TmpRoomIndex, 1, true);
			}
			// FCoordsAvailableRooms.RemoveAt((int32) TmpRoomIndex, 1, true);
			// UE_LOG(LogTemp, Warning, TEXT("Number of Available Rooms: %d"), FCoordsAvailableRooms.Num());
			remaining--;
		}
	}
}

// Gets the address of the level grid
uint8* AProceduralGridLevel::GetLevelGrid()
{
	return *Level;
}

// Returns the Coordinates of the starting spawn room
FVector AProceduralGridLevel::GetStartingSpawnCoords()
{
	return FStartingSpawn;
}

// Randomly picks the starting room
void AProceduralGridLevel::CreateInitialRoom()
{
	uint8 x, y;
	x = FMath::RandRange(3, 7);
	y = FMath::RandRange(3, 7);

	Level[x][y] = (uint8)ERoomType::ERoom_Basic;
	SetRoomsToAvailable(x, y);

	FActorSpawnParameters SpawnInfo;
	SpawnInfo.bNoFail = false;
	SpawnInfo.Owner = this;
	SpawnInfo.Instigator = NULL;
	SpawnInfo.bDeferConstruction = false;

	FStartingCoords = FCoords();
	FStartingCoords.Row = x;
	FStartingCoords.Col = y;
	FStartingSpawn = FVector((x * ROOM_DIMENSION_X), (y * ROOM_DIMENSION_Y), 100);

	AIsaacClonePawn* Pawn = GetWorld()->SpawnActor<AIsaacClonePawn>(AIsaacClonePawn::StaticClass(), FStartingSpawn, FRotator::ZeroRotator, SpawnInfo);
	APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
	AIsaacClonePawn* OriginalPawn = (AIsaacClonePawn*) PlayerController->GetPawn();
	OriginalPawn->Destroy();
	PlayerController->Possess(Pawn);
	Pawn->Tags.Add(FName("Player"));
	// UE_LOG(LogTemp, Warning, TEXT("PlayerPossessed"));
}

// Checks and sets the rooms adjacent to the given coordinates in the level grid to available
void AProceduralGridLevel::SetRoomsToAvailable(uint8 xPos, uint8 yPos)
{
	if (xPos + 1 >= LEVEL_SIZE || xPos - 1 < 0 || yPos + 1 >= LEVEL_SIZE || yPos - 1 < 0) {
		return;
	}
	// Check North of room
	if (Level[xPos][yPos - 1] == (uint8)ERoomType::ERoom_Empty) {
		Level[xPos][yPos - 1] = (uint8)ERoomType::ERoom_Available;
		AddAvailableRoomToQueue(xPos, yPos - 1);
	}
	// Check West of room
	if (Level[xPos - 1][yPos] == (uint8)ERoomType::ERoom_Empty) {
		Level[xPos - 1][yPos] = (uint8)ERoomType::ERoom_Available;
		AddAvailableRoomToQueue(xPos - 1, yPos);
	}
	// Check South of room
	if (Level[xPos][yPos + 1] == (uint8)ERoomType::ERoom_Empty) {
		Level[xPos][yPos + 1] = (uint8)ERoomType::ERoom_Available;
		AddAvailableRoomToQueue(xPos, yPos + 1);
	}
	// Check East of room
	if (Level[xPos + 1][yPos] == (uint8)ERoomType::ERoom_Empty) {
		Level[xPos + 1][yPos] = (uint8)ERoomType::ERoom_Available;
		AddAvailableRoomToQueue(xPos + 1, yPos);
	}
}

// Adds each room adjacent to the room given in the coordinates to the availability queue
void AProceduralGridLevel::AddAvailableRoomToQueue(uint8 xPos, uint8 yPos)
{
	FCoords* FCoordsAvailableRoom = new FCoords();
	FCoordsAvailableRoom->Row = xPos;
	FCoordsAvailableRoom->Col = yPos;
	FCoordsAvailableRooms.Add(FCoordsAvailableRoom);
}

// Set the base number of rooms for the level
void AProceduralGridLevel::SetNumberOfRooms(uint8 rooms)
{
	NumberOfRooms = rooms;
}

// Get the base number of rooms for the level
uint8 AProceduralGridLevel::GetNumberOfRooms()
{
	return NumberOfRooms;
}

// Checks if there is room for a Big Room given the coordinates within the level grid
bool AProceduralGridLevel::CheckIfAbleToPlaceBigRoom(uint8 xPos, uint8 yPos)
{

	// right = +y = east, left = -y = west
	// up = +x = north, down = -x = south
	bool bHasRoom = true;

	if (xPos + 1 < LEVEL_SIZE && yPos + 1 < LEVEL_SIZE) {
		// Check if able to place Big Room to the east and south of current room
		if (Level[xPos + 1][yPos] == (uint8)ERoomType::ERoom_Empty &&
			Level[xPos][yPos + 1] == (uint8)ERoomType::ERoom_Empty &&
			Level[xPos + 1][yPos + 1] == (uint8)ERoomType::ERoom_Empty) {
			// Add rooms
			Level[xPos][yPos] = (uint8)ERoomType::ERoom_BigC;
			Level[xPos + 1][yPos] = (uint8)ERoomType::ERoom_BigA;
			Level[xPos][yPos + 1] = (uint8)ERoomType::ERoom_BigD;
			Level[xPos + 1][yPos + 1] = (uint8)ERoomType::ERoom_BigB;
			SetRoomsToAvailable(xPos, yPos);
			SetRoomsToAvailable(xPos + 1, yPos);
			SetRoomsToAvailable(xPos, yPos + 1);
			SetRoomsToAvailable(xPos + 1, yPos + 1);
			return bHasRoom;
		}
	}

	if (xPos + 1 < LEVEL_SIZE && yPos - 1 > 0) {
		// Check if able to place Big Room to the east and north of current room
		if (Level[xPos][yPos - 1] == (uint8)ERoomType::ERoom_Empty &&
			Level[xPos + 1][yPos] == (uint8)ERoomType::ERoom_Empty &&
			Level[xPos + 1][yPos - 1] == (uint8)ERoomType::ERoom_Empty) {
			// Add rooms
			Level[xPos][yPos] = (uint8)ERoomType::ERoom_BigD;
			Level[xPos + 1][yPos] = (uint8)ERoomType::ERoom_BigB;
			Level[xPos][yPos - 1] = (uint8)ERoomType::ERoom_BigC;
			Level[xPos + 1][yPos - 1] = (uint8)ERoomType::ERoom_BigA;
			SetRoomsToAvailable(xPos, yPos);
			SetRoomsToAvailable(xPos + 1, yPos);
			SetRoomsToAvailable(xPos, yPos - 1);
			SetRoomsToAvailable(xPos + 1, yPos - 1);
			return bHasRoom;
		}
	}

	// Check if able to place Big Room to the west and south of current room
	if (xPos - 1 > 0 && yPos + 1 < LEVEL_SIZE) {
		if (Level[xPos - 1][yPos] == (uint8)ERoomType::ERoom_Empty &&
			Level[xPos][yPos + 1] == (uint8)ERoomType::ERoom_Empty &&
			Level[xPos - 1][yPos + 1] == (uint8)ERoomType::ERoom_Empty) {
			// Add rooms
			Level[xPos][yPos] = (uint8)ERoomType::ERoom_BigA;
			Level[xPos - 1][yPos] = (uint8)ERoomType::ERoom_BigC;
			Level[xPos][yPos + 1] = (uint8)ERoomType::ERoom_BigB;
			Level[xPos - 1][yPos + 1] = (uint8)ERoomType::ERoom_BigD;
			SetRoomsToAvailable(xPos, yPos);
			SetRoomsToAvailable(xPos - 1, yPos);
			SetRoomsToAvailable(xPos, yPos + 1);
			SetRoomsToAvailable(xPos - 1, yPos + 1);
			return bHasRoom;
		}
	}
	if (xPos - 1 > 0 && yPos - 1 > 0) {
		// Check if able to place Big Room to the west and north of current room
		if (Level[xPos - 1][yPos] == (uint8)ERoomType::ERoom_Empty &&
			Level[xPos][yPos - 1] == (uint8)ERoomType::ERoom_Empty &&
			Level[xPos - 1][yPos - 1] == (uint8)ERoomType::ERoom_Empty) {
			// Add rooms
			Level[xPos][yPos] = (uint8)ERoomType::ERoom_BigB;
			Level[xPos - 1][yPos] = (uint8)ERoomType::ERoom_BigD;
			Level[xPos][yPos - 1] = (uint8)ERoomType::ERoom_BigA;
			Level[xPos - 1][yPos - 1] = (uint8)ERoomType::ERoom_BigC;
			SetRoomsToAvailable(xPos, yPos);
			SetRoomsToAvailable(xPos - 1, yPos);
			SetRoomsToAvailable(xPos, yPos - 1);
			SetRoomsToAvailable(xPos - 1, yPos - 1);
			return bHasRoom;
		}
	}
	bHasRoom = false;
	return bHasRoom;
}

// Goes through the entire list of available rooms and makes sure that they are actually available
void AProceduralGridLevel::refreshAvailableRooms()
{
	for (int i = FCoordsAvailableRooms.Num() - 1; i >= 0; --i) {
		int x = FCoordsAvailableRooms[i]->Row;
		int y = FCoordsAvailableRooms[i]->Col;
		if (Level[x][y] != (uint8)ERoomType::ERoom_Available) {
			FCoordsAvailableRooms.RemoveAt(i);
		}
	}
}

void AProceduralGridLevel::AddBossRoom(FCoords StartingRoom)
{
	TArray<FCoords> Queue = TArray<FCoords>();
	uint8 maxDist = 0;

	// Initiate the array to zero

	uint8 distance[LEVEL_SIZE][LEVEL_SIZE];
	for (int row = 0; row < LEVEL_SIZE; row++) {
		for (int col = 0; col < LEVEL_SIZE; col++) {
			distance[row][col] = 0;
		}
	}
	// Set the Starting room to have 0 distance
	// distance[StartingRoom.Row][StartingRoom.Col] = 0;

	FCoords node = FCoords();
	node.Row = StartingRoom.Row;
	node.Col = StartingRoom.Col;
	Queue.Add(node);

	while (Queue.Num() != 0) {
		// UE_LOG(LogTemp, Warning, TEXT("Queue Size: %d"), Queue.Num());
		FCoords front = Queue[0];
		Queue.RemoveAt(0);

		//UE_LOG(LogTemp, Warning, TEXT("Front Row: %d"), front.Row);
		//UE_LOG(LogTemp, Warning, TEXT("Front Col: %d"), front.Col);

		// Check above
		if ((distance[front.Row + 1][front.Col] == 0) && (Level[front.Row + 1][front.Col] != (uint8)ERoomType::ERoom_Empty)
			&& (front.Row + 1 < LEVEL_SIZE)) {
			// Set distance
			distance[front.Row + 1][front.Col] = distance[front.Row][front.Col] + 1;

			// Add new node to Queue
			FCoords tmp = FCoords();
			tmp.Row = front.Row + 1;
			tmp.Col = front.Col;
			Queue.Add(tmp);
		}

		// Check below
		if ((distance[front.Row - 1][front.Col] == 0) && (Level[front.Row - 1][front.Col] != (uint8)ERoomType::ERoom_Empty)
			&& (front.Row - 1 >= 0)) {
			// Set distance
			distance[front.Row - 1][front.Col] = distance[front.Row][front.Col] + 1;

			// Add new node to Queue
			FCoords tmp = FCoords();
			tmp.Row = front.Row - 1;
			tmp.Col = front.Col;
			Queue.Add(tmp);
		}

		// Check to the right
		if ((distance[front.Row][front.Col + 1] == 0) && (Level[front.Row][front.Col + 1] != (uint8)ERoomType::ERoom_Empty)
			&& (front.Col + 1 < LEVEL_SIZE)) {
			// Set distance
			distance[front.Row][front.Col + 1] = distance[front.Row][front.Col] + 1;

			// Add new node to Queue
			FCoords tmp = FCoords();
			tmp.Row = front.Row ;
			tmp.Col = front.Col + 1;
			Queue.Add(tmp);
		}

		// Check to the left
		if ((distance[front.Row][front.Col - 1] == 0) && (Level[front.Row][front.Col - 1] != (uint8)ERoomType::ERoom_Empty)
			&& (front.Col - 1 >= 0)) {
			// Set distance
			distance[front.Row][front.Col - 1] = distance[front.Row][front.Col] + 1;

			// Add new node to Queue
			FCoords tmp = FCoords();
			tmp.Row = front.Row;
			tmp.Col = front.Col - 1;
			Queue.Add(tmp);
		}
	}
	
	// Find the max distance
	for (int row = 0; row < LEVEL_SIZE; row++) {
		for (int col = 0; col < LEVEL_SIZE; col++) {
			if (distance[row][col] > maxDist) {
				maxDist = distance[row][col];
			}
		}
	}

	// Print Distance array ----------------------
	FString grid = "";
	// FString grid2 = "";
	for (int i = 0; i < LEVEL_SIZE; ++i) {
		for (int j = 0; j < LEVEL_SIZE; ++j) {
			grid.AppendInt(distance[i][j]);
			//grid2.AppendInt(j);
		}
		grid.Append("\n");
		// grid2.Append("\n");
	}
	UE_LOG(LogTemp, Warning, TEXT("%s"), *grid);
	// -------------------------------------------------

	// Add them to an array and randomly pick one
	for (int row = 0; row < LEVEL_SIZE; row++) {
		for (int col = 0; col < LEVEL_SIZE; col++) {
			if (distance[row][col] == maxDist) {
				FCoords tmp = FCoords();
				tmp.Row = row;
				tmp.Col = col;
				Queue.Add(tmp);
			}
		}
	}

	FCoords BossRoomCoords = Queue[(uint8) FMath::RandRange(0, Queue.Num() - 1)];

	Level[BossRoomCoords.Row][BossRoomCoords.Col] = (uint8) ERoomType::ERoom_BossRoom;
	//FVector Location = FVector(BossRoomCoords.Row * ROOM_DIMENSION_X, BossRoomCoords.Col * ROOM_DIMENSION_Y, 0);
	//GetWorld()->SpawnActor(SpawnBasicRoom, &Location, &FRotator::ZeroRotator);
}


void AProceduralGridLevel::AddItemRoom()
{

}

void AProceduralGridLevel::AddDoorsToRoom(uint32 X, uint32 Y, ARoom* Room)
{
	uint32 Row = X;
	uint32 Col = Y;
	//UE_LOG(LogTemp, Warning, TEXT("Col: %d"), Col);
	//UE_LOG(LogTemp, Warning, TEXT("Row: %d"), Row);
	if (Col + 1 >= LEVEL_SIZE) {
		Room->bEastDoor = true;
	}
	if (Col - 1 < 0) {
		Room->bWestDoor = true;
	}
	if (Row + 1 >= LEVEL_SIZE) {
		Room->bNorthDoor = true;
	}
	if (Row - 1 < 0) {
		Room->bSouthDoor = true;
	}
}

void AProceduralGridLevel::printGrid()
{
	FString grid = "";
	// FString grid2 = "";
	for (int i = 0; i < LEVEL_SIZE; ++i) {
		for (int j = 0; j < LEVEL_SIZE; ++j) {
			grid.AppendInt((uint8)Level[i][j]);
			//grid2.AppendInt(j);
		}
		grid.Append("\n");
		// grid2.Append("\n");
	}
	UE_LOG(LogTemp, Warning, TEXT("%s"), *grid);
	// UE_LOG(LogTemp, Warning, TEXT("%s"), *grid2);
}

void AProceduralGridLevel::SpawnRoom(ERoomType roomType, uint32 X, uint32 Y) 
{
	UWorld* World = GetWorld();
	ARoom* Room;
	FVector Location = FVector(X, Y, 0);
	FRotator Rotation = FRotator::ZeroRotator;
	switch (roomType) {
	case (ERoomType::ERoom_Basic):
		Room = (ARoom*) World->SpawnActor(SpawnBasicRoom, &Location, &Rotation);
		AddDoorsToRoom(X / ROOM_DIMENSION_X, Y / ROOM_DIMENSION_Y, Room);
		break;
	case (ERoomType::ERoom_BigC):
		Location = FVector(X - 340, Y - 460 , 0);
		//World->SpawnActor(SpawnBigRoomC, &Location, &Rotation);
		break;
	case (ERoomType::ERoom_BigA):
		// Location = FVector(X + 340, Y - 460, 0);
		Location = FVector(X - 850, Y + 1150, 0);
		Room = (ARoom*) World->SpawnActor(SpawnBigRoomA, &Location, &Rotation);
		AddDoorsToRoom((X + 1) / ROOM_DIMENSION_X, (Y + 1) / ROOM_DIMENSION_Y, Room);
		AddDoorsToRoom((X - 1) / ROOM_DIMENSION_X, (Y - 1) / ROOM_DIMENSION_Y, Room);
		break;
	case (ERoomType::ERoom_BigD):
		Location = FVector(X - 340, Y + 460, 0);
		//World->SpawnActor(SpawnBigRoomD, &Location, &Rotation);
		break;
	case (ERoomType::ERoom_BigB):
		Location = FVector(X + 340, Y + 460, 0);
		//World->SpawnActor(SpawnBigRoomB, &Location, &Rotation);
		break;

	case(ERoomType::ERoom_BossRoom):
		Room = (ARoom*) World->SpawnActor(SpawnBasicRoom, &Location, &Rotation);
		AddDoorsToRoom(X / ROOM_DIMENSION_X, Y / ROOM_DIMENSION_Y, Room);
		break;

	// Default - spawn an empty room
	default:
		Location = FVector(X, Y, 180);
		World->SpawnActor(SpawnEmptyRoom, &Location, &Rotation);
		break;
	}

	// A - Location = FVector(X + 340, Y - 460, 110);
	// B - Location = FVector(X + 340, Y + 460, 110);
	// C - Location = FVector(X - 340, Y - 460, 110);
	// D - Location = FVector(X - 340, Y + 460, 110);
}

void AProceduralGridLevel::SpawnLevel()
{
	uint32 y = ROOM_DIMENSION_Y;
	uint32 x = ROOM_DIMENSION_X;

	for (uint8 col = 0; col < LEVEL_SIZE; ++col) {
		for (uint8 row = 0; row < LEVEL_SIZE; ++row) {
				SpawnRoom((ERoomType)Level[col][row], x * col, y * row);
				// UE_LOG(LogTemp, Warning, TEXT("%d"), Level[col][row]);
		}
	}
}

