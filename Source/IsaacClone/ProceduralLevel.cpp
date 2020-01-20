// Fill out your copyright notice in the Description page of Project Settings.

#include "ProceduralLevel.h"
#include "Engine/Classes/Components/InstancedStaticMeshComponent.h"


// Sets default values
AProceduralLevel::AProceduralLevel()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Default Settings
	maxRooms = 25;
	maxRoomSize = 100;
	minRoomSize = 50;
	placementTries = 100;
	tileSize = 100;
	mazeSize = 100;

	USceneComponent* RootSceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
	RootComponent = RootSceneComponent;

	room = CreateDefaultSubobject<UInstancedStaticMeshComponent>(TEXT("Room"));
	corridor = CreateDefaultSubobject<UInstancedStaticMeshComponent>(TEXT("Corridor"));

	UStaticMesh* Mesh = LoadObject<UStaticMesh>(nullptr, TEXT("StaticMesh'/Game/Geometry/Meshes/1M_Cube.1M_Cube'"));
	room->SetStaticMesh(Mesh);

	room->SetupAttachment(RootComponent);
	corridor->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void AProceduralLevel::BeginPlay()
{
	Super::BeginPlay();

	GenerateLevel();
	centers = GetCenterOfRooms(roomPositions, roomSizes);
	edges = CreateMST(centers);
	CreateInitialCorridors(roomPositions, roomSizes);
	for (int i = 0; i < roomPositions.Num(); ++i) {
		SpawnRooms(roomPositions[i], roomSizes[i], room);
	}
}

// Called every frame
void AProceduralLevel::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Generates a random level
void AProceduralLevel::GenerateLevel()
{
	FVector position;
	FVector size;
	int32 tries = 0;
	while (tries < placementTries && roomPositions.Num() < maxRooms) {
		if (TryToPlaceRoom(position, size)) {
			roomPositions.Add(position);
			roomSizes.Add(size);
			tries = 0;
		}
		else {
			tries++;
		}
	}
	return;
}

bool AProceduralLevel::TryToPlaceRoom(FVector& OUTPosition, FVector& OUTSize)
{
	bool notOverlapping = true;
	FVector position, size;
	GenerateRoom(position, size);
	for (int i = 0; i < roomPositions.Num(); i++) {
		if (IsOverlapping(position, size, roomPositions[i], roomSizes[i])) {
			notOverlapping = false;
			return notOverlapping;
		}
	}
	if (notOverlapping) {
		OUTPosition = FVector(position.X, position.Y, 0);
		OUTSize = FVector(size.X, size.Y, 0);
		return notOverlapping;
	}
	return !notOverlapping;
}

void AProceduralLevel::GenerateRoom(FVector& OUTRoomPosition, FVector& OUTRoomSize)
{
	// Randomly generate a room size
	int32 xSize = FMath::RandRange(minRoomSize, maxRoomSize);
	int32 ySize = FMath::RandRange(minRoomSize, maxRoomSize);
	OUTRoomSize = FVector(xSize, ySize, 0);

	// Randomly generate the room's position
	int32 xPos = FMath::RandRange(0, (mazeSize - xSize));
	int32 yPos = FMath::RandRange(0, (mazeSize - ySize));
	OUTRoomPosition = FVector(xPos, yPos, 0);
}

// Checks if the positions of room1 and room2 overlap
bool AProceduralLevel::IsOverlapping(const FVector pos1, const FVector size1, const FVector pos2, const FVector size2)
{
	// Calculate the positions of room 1
	int32 x1_min = pos1.X;
	int32 x1_max = pos1.X + size1.X;

	int32 y1_min = pos1.Y;
	int32 y1_max = pos1.Y + size1.Y;

	// Calculate the positions of room 2
	int32 x2_min = pos2.X;
	int32 x2_max = pos2.X + size2.X;

	int32 y2_min = pos2.Y;
	int32 y2_max = pos2.Y + size2.Y;

	// Checks If the the min X & min Y coord-position of room 2 is less than the max X ana coord-position of room 2 
	if (x1_max < x2_min || x1_min > x2_max || y1_min > y2_max || y1_max < y2_min) {
		return false;
	}
	else {
		return true;
	}
}

TArray<FVector> AProceduralLevel::GetCenterOfRooms(const TArray<FVector>& positions, const TArray<FVector>& sizes)
{
	TArray<FVector> roomCenters = TArray<FVector>();
	float x, y;
	for (int i = 0; i < positions.Num(); i++) {
		x = positions[i].X + (sizes[i].X / 2);
		y = positions[i].Y + (sizes[i].Y / 2);
		roomCenters.Emplace(FVector(x, y, i));
	}
	return roomCenters;
}

TArray<FIntVector> AProceduralLevel::CreateMST(TArray<FVector>& rooms)
{
	TArray<FVector> mst = TArray<FVector>(); // the completed tree
	TArray<FIntVector> edges = TArray<FIntVector>();

	// Add the first room in the array as the starting vertex for the tree and remove from remaining rooms
	mst.Emplace(FVector(rooms[0].X, rooms[0].Y, 0));
	rooms.RemoveAt(0);
	int counter = 0;
	// Using Prim's Algorithm, we generate a MST for the remaining rooms
	while (rooms.Num() > 0) { // rooms.Num() > 0
		FIntVector edge = CreateMSTHelper(mst, rooms);
		//FString s = FString::FromInt(edge.X);
		//int d = edge.Y;
		//UE_LOG(LogTemp, Warning, TEXT("mst: %s"), *s);
		//UE_LOG(LogTemp, Warning, TEXT("remaining: %d"), d);
		if (edge.X > -1 && edge.Y > -1) {
			edges.Emplace(FIntVector(mst[edge.X].Z, rooms[edge.Y].Z, 0));
			mst.Emplace(FVector(rooms[edge.Y].X, rooms[edge.Y].Y, rooms[edge.Y].Z));
			rooms.RemoveAt(edge.Y);
			FString s = FString::FromInt(rooms.Num());
			UE_LOG(LogTemp, Warning, TEXT("%s"), *s);
			counter++;
		}

		//edges.Emplace(FIntVector(mst[edge.X].Z, rooms[edge.Y].Z, 0));
		//mst.Add(rooms[edge.X]);
		//rooms.RemoveAt(edge.Y);
	}

	// test edge
	// edges.Emplace(FIntVector(1, 1, 0));

	return edges;
}

// Finds the minimal distance between rooms and adds an edge between the two (Prim's Algorithm)
FIntVector AProceduralLevel::CreateMSTHelper(const TArray<FVector>& completed, const TArray<FVector>& remaining)
{
	//int32 tmpRoomIndex = -1;
	//int32 tmpRemainIndex = -1;
	int32 minIndexRoom = -1;
	int32 minIndexRemain = -1;
	float tmpDist = 0;
	float minDist = TNumericLimits<float>::Max();
	FVector tmpComp, tmpRemain;

	// Searches for the minimum distance between the current tree to the remaining vertices outside of the tree and add an edge to the shortest closest vertex
	//for (FVector room : completed) {
	//	tmpComp = FVector(room.X, room.Y, 0);
	//	//tmpRoomIndex = room.Z;
	//	for (FVector remainder : remaining) {
	//		//tmpRemainIndex = remainder.Z;
	//		tmpRemain = FVector(remainder.X, remainder.Y, 0);
	//		tmpDist = FVector::Dist(tmpComp, tmpRemain);
	//		tmpDist = FMath::Abs(tmpDist);
	//		if (tmpDist < minDist) {
	//			minDist = tmpDist;
	//			minIndexRoom = room.Z;
	//			minIndexRemain = remainder.Z;
	//			//FString s = FString::FromInt(remainder.X);
	//			//FString d = FString::FromInt(remainder.Y);
	//			//UE_LOG(LogTemp, Warning, TEXT("completed: %s"), *s);
	//			//UE_LOG(LogTemp, Warning, TEXT("reamaining: %s"), *d);
	//		}
	//	}
	//}

	for (int roomIndex = 0; roomIndex < completed.Num(); ++roomIndex) {
		tmpComp = FVector(completed[roomIndex].X, completed[roomIndex].Y, 0);
		for (int remainIndex = 0; remainIndex < remaining.Num(); ++remainIndex) {
			tmpRemain = FVector(remaining[remainIndex].X, remaining[remainIndex].Y, 0);
			tmpDist = FVector::Dist(tmpComp, tmpRemain);
			tmpDist = FMath::Abs(tmpDist);
			if (tmpDist < minDist) {
				minDist = tmpDist;
				minIndexRoom = roomIndex;
				minIndexRemain = remainIndex;
			}
		}
	}
	return FIntVector(minIndexRoom, minIndexRemain, 0);
}

void AProceduralLevel::CreateInitialCorridors(const TArray<FVector>& positions, const TArray<FVector>& sizes)
{
	FVector aPos, aSize, bPos, bSize;
	FVector corridA, corridB;
	int32 min, max;
	int32 x, y;
	for (FIntVector edge : edges) {
		// Get the room position and sizes of each room
		aPos = positions[edge.X];
		bPos = positions[edge.Y];
		aSize = sizes[edge.X];
		bSize = sizes[edge.Y];

		// Create horizontal / vertical corridors, only if the room A and room B overlap in some x or y coordinate
		float xMax = FMath::Max(aPos.X, bPos.X);
		float xMin = FMath::Min((aPos.X + aSize.X), (bPos.X + bSize.X));

		// Check if there is a Y overlap
		float yMax = FMath::Max(aPos.Y, bPos.Y);
		float yMin = FMath::Min((aPos.Y + aSize.Y), (bPos.Y + bSize.Y));

		// Check if there is an X overlap
		if (xMax <= xMin) {
			// Check which room is above the other
			// room A is higher than room B
			if (bPos.Y <= aPos.Y) {
				min = FMath::Max(aPos.X, bPos.X);
				max = FMath::Min(aPos.X + aSize.X, bPos.X + bSize.X);
				x = FMath::RandRange(min, max);
				//corridA = FVector(x, aPos.Y, 0);
				//corridB = FVector(x, bPos.Y + bSize.Y, 0);
				roomCorridorStart.Emplace(FVector(x, aPos.Y, 0));
				roomCorridorEnd.Emplace(FVector(x, bPos.Y + bSize.Y, 0));
			}
			// room B is higher than room A
			if (aPos.Y <= bPos.Y) {
				min = FMath::Max(aPos.X, bPos.X);
				max = FMath::Min(aPos.X + aSize.X, bPos.X + bSize.X);
				x = FMath::RandRange(min, max);
				//corridA = FVector(x, aPos.Y + aSize.Y, 0);
				//corridB = FVector(x, bPos.Y, 0);
				roomCorridorStart.Emplace(FVector((aPos.X + aSize.X), y, 0));
				roomCorridorEnd.Emplace(FVector(bPos.X, y, 0));
			}
		}
		else if (yMax <= yMin) {
			// Check if room B is to the left of room A
			if (bPos.X <= aPos.X) {
				min = FMath::Max(aPos.Y, bPos.Y);
				max = FMath::Min((aPos.Y + aSize.Y), (bPos.Y + bSize.Y));
				y = FMath::RandRange(min, max);
				//corridA = FVector(aPos.X, y, 0);
				//corridB = FVector((bPos.X + bSize.X), y, 0);
				roomCorridorStart.Emplace(FVector(aPos.X, y, 0));
				roomCorridorEnd.Emplace(FVector((bPos.X + bSize.X), y, 0));
			}

			// Check if room B is to the right of room A
			if (aPos.X <= bPos.X) {
				min = FMath::Max(aPos.Y, bPos.Y);
				max = FMath::Min((aPos.Y + aSize.Y), (bPos.Y + bSize.Y));
				y = FMath::RandRange(min, max);
				//corridA = FVector((aPos.X + aSize.X), y, 0);
				//corridB = FVector(bPos.X, y, 0);
				roomCorridorStart.Emplace(FVector((aPos.X + aSize.X), y, 0));
				roomCorridorEnd.Emplace(FVector(bPos.X, y, 0));
			}
		}
		// Check if there is no overlap
		else {
			float r = FMath::FRand();
			// Create corridors that join the two rooms when they share no overlap
			// Randomly pick a type of corridor
			// case 1: If room B is to the top right of room A - good
			if (((aPos.X + aSize.X) <= bPos.X) && ((aPos.Y + aSize.Y) >= bPos.Y)) {
				CreateJointCorridor(bPos, bSize, aPos, aSize, aPos.X + aSize.X, aPos.Y + aSize.Y, bPos.X, bPos.Y);
				//// Create corridor type A
				//if (r <= 0.5) {
				//	FVector aDoor = FVector(x, (aPos.Y + aSize.Y), 0);
				//	FVector bDoor = FVector(bPos.X, y, 0);
				//}
				//// Create corridor type B
				//else {
				//	FVector aDoor = FVector((aPos.X + aSize.X), y, 0);
				//	FVector bDoor = FVector(x, bPos.Y, 0);
				//}
			}

			// case 2: If room B is to the top left of room A - good
			if ((aPos.X >= (bPos.X + bSize.X)) && ((aPos.Y + aSize.Y) <= bPos.Y)) {
				CreateJointCorridor(bPos, bSize, aPos, aSize, aPos.X, aPos.Y + aSize.Y, bPos.X + bSize.X, bPos.Y);
				// Create corridor type A
				//if (r <= 0.5) {
				//	FVector aDoor = FVector(x, (aPos.Y + aSize.Y), 0);
				//	FVector bDoor = FVector((bPos.X + bSize.X), y, 0);
				//}
				//// Create corridor type B
				//else {
				//	FVector aDoor = FVector(aPos.X, y, 0);
				//	FVector bDoor = FVector(x, bPos.Y, 0);
				//}
			}

			// case 3: If room B is to the bottom left of room A - good
			if (aPos.X >= (bPos.X + bSize.X) && (aPos.Y >= (bPos.Y + bSize.Y))) {
				CreateJointCorridor(bPos, bSize, aPos, aSize, aPos.X, aPos.Y, bPos.X + bSize.X, bPos.Y + bSize.Y);
				// Create corridor type A
				//if (r <= 0.5) {
				//	FVector aDoor = FVector(x, aPos.Y, 0);
				//	FVector bDoor = FVector((bPos.X + bSize.X), y, 0);
				//}
				//// Create corridor type B
				//else {
				//	FVector aDoor = FVector(aPos.X, y, 0);
				//	FVector bDoor = FVector(x, (bPos.Y + bSize.Y), 0);
				//}
			}

			// case 4: If room B is to the bottom right of room A - good
			if (((aPos.X + aSize.X) <= bPos.X) && (aPos.Y >= (bPos.Y + bSize.Y))) {
				CreateJointCorridor(bPos, bSize, aPos, aSize, aPos.X + aSize.X, aPos.Y, bPos.X, bPos.Y + bSize.Y);
				//// Create corridor type A
				//if (r <= 0.5) {
				//	FVector aDoor = FVector(x, aPos.Y, 0);
				//	FVector bDoor = FVector(bPos.X, y, 0);
				//}
				//// Create corridor type B
				//else {
				//	FVector aDoor = FVector((aPos.X + aSize.X), y, 0);
				//	FVector bDoor = FVector(x, (bPos.Y + bSize.Y), 0);
				//}
			}
		}
	}
}

void AProceduralLevel::CreateJointCorridor(FVector &bPos, FVector &bSize, FVector &aPos, FVector &aSize, int32 aX, int32 aY, int32 bX, int32 bY)
{
	float r = FMath::FRand();
	FVector aDoor, bDoor, cMidPoint;
	int32 x, y;
	// Create corridor type A
	if (r <= 0.5) {
		y = FMath::RandRange(bPos.Y, bPos.Y + bSize.Y);
		x = FMath::RandRange(aPos.X, aPos.X + aSize.X);
		aDoor = FVector(x, aY, 0);
		bDoor = FVector(bX, y, 0);
		cMidPoint = FVector(x, y, 0);
	}
	// Create corridor type B
	else {
		y = FMath::RandRange(aPos.Y, aPos.Y + aSize.Y);
		x = FMath::RandRange(bPos.X, bPos.X + bSize.X);
		aDoor = FVector(aX, y, 0);
		bDoor = FVector(x, bY, 0);
		cMidPoint = FVector(x, y, 0);
	}
	roomCorridorStart.Add(aDoor);
	roomCorridorStart.Add(bDoor);
	roomCorridorEnd.Add(cMidPoint);
	roomCorridorEnd.Add(cMidPoint);
}


void AProceduralLevel::SpawnRooms(const FVector position, const FVector size, UInstancedStaticMeshComponent* room)
{
	int32 X = size.X;
	int32 Y = size.Y;
	FVector tmp;
	FTransform transform;
	for (int i = 0; i < X; i++) {
		for (int j = 0; j < Y; j++) {
			tmp = FVector(i * tileSize, j * tileSize, 0) + (position * tileSize);
			transform = FTransform(tmp);
			room->AddInstance(transform);
		}
	}
}


void AProceduralLevel::SpawnCorridor(const FVector & start, const FVector & end, UInstancedStaticMeshComponent* corridor)
{
	FTransform transform = FTransform();
	//transform.SetTranslation(start);
	//transform.SetScale3D(end);
	corridor->AddInstance(transform);
}

void AProceduralLevel::SpawnFloor(const float levelSize)
{
}



