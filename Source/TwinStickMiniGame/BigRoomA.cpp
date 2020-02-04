// Fill out your copyright notice in the Description page of Project Settings.

#include "BigRoomA.h"
ABigRoomA::ABigRoomA()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	InitRoomMeshes();
}

void ABigRoomA::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (bPlayerEntered && !bIsCleared) {
		BoxComponent->GetOverlappingActors(Enemies, AEnemyCharacter::StaticClass());
		// UE_LOG(LogTemp, Warning, TEXT("Enemies Left: %d"), Enemy.Num());
		if (Enemies.Num() == 0) {
			//UE_LOG(LogTemp, Warning, TEXT("IsCleared: %s"), (bIsCleared ? TEXT("True") : TEXT("False")));
			bIsCleared = true;
			OpenDoorsOnClear();
			//UE_LOG(LogTemp, Warning, TEXT("IsCleared: %s"), (bIsCleared ? TEXT("True") : TEXT("False")));
		}
	}
}

void ABigRoomA::BeginPlay()
{
	Super::BeginPlay();
}

void ABigRoomA::InitRoomMeshes() {
	//USceneComponent* RootSceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
	//RootComponent = RootSceneComponent;

	URoomComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Big Room A"));
	// URoomMesh = LoadObject<UStaticMesh>(nullptr, TEXT("StaticMesh'/Game/Level/Meshes/Big_Room_A.Big_Room_A'"));
	URoomMesh = LoadObject<UStaticMesh>(nullptr, TEXT("StaticMesh'/Game/Level/Meshes/Big_Room.Big_Room'"));
	URoomComponent->SetStaticMesh(URoomMesh);
	URoomComponent->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);

	FVector scale = FVector(50.5f, 69.5f, 5.0f);
	BoxComponent->SetRelativeScale3D(scale);
	BoxComponent->SetRelativeLocation(FVector(0, 0, 50));

}

void ABigRoomA::CloseAllDoors()
{
	// North Doors
	CloseNorthDoors();

	// South Doors
	CloseSouthDoors();

	// East Doors
	CloseEastDoors();

	// West Doors
	CloseWestDoors();
}

void ABigRoomA::CloseNorthDoors()
{
	FTransform Transform;
	Transform.SetLocation(URoomComponent->GetSocketLocation(FName("NorthWestDoor")));
	DoorMesh->AddInstance(Transform);
	Transform.SetLocation(URoomComponent->GetSocketLocation(FName("NorthEastDoor")));
	DoorMesh->AddInstance(Transform);
}

void ABigRoomA::CloseSouthDoors()
{
	FTransform Transform;
	Transform.SetLocation(URoomComponent->GetSocketLocation(FName("SouthWestDoor")));
	DoorMesh->AddInstance(Transform);
	Transform.SetLocation(URoomComponent->GetSocketLocation(FName("SouthEastDoor")));
	DoorMesh->AddInstance(Transform);
}

void ABigRoomA::CloseWestDoors()
{
	FTransform Transform;
	Transform.SetLocation(URoomComponent->GetSocketLocation(FName("WestNorthDoor")));
	DoorMesh->AddInstance(Transform);
	Transform.SetLocation(URoomComponent->GetSocketLocation(FName("WestSouthDoor")));
	DoorMesh->AddInstance(Transform);
}

void ABigRoomA::CloseEastDoors()
{
	FTransform Transform;
	Transform.SetLocation(URoomComponent->GetSocketLocation(FName("EastNorthDoor")));
	DoorMesh->AddInstance(Transform);
	Transform.SetLocation(URoomComponent->GetSocketLocation(FName("EastSouthDoor")));
	DoorMesh->AddInstance(Transform);
}


void ABigRoomA::OpenDoorsOnClear()
{
	//UE_LOG(LogTemp, Warning, TEXT("North: %s"), (bNorthDoor ? TEXT("True") : TEXT("False")));
	//UE_LOG(LogTemp, Warning, TEXT("South: %s"), (bSouthDoor ? TEXT("True") : TEXT("False")));
	//UE_LOG(LogTemp, Warning, TEXT("East: %s"), (bEastDoor ? TEXT("True") : TEXT("False")));
	//UE_LOG(LogTemp, Warning, TEXT("West: %s"), (bWestDoor ? TEXT("True") : TEXT("False")));
	DoorMesh->ClearInstances();
	if (bNorthDoor) {
		CloseNorthDoors();
	}
	if (bSouthDoor) {
		CloseSouthDoors();
	}
	if (bEastDoor) {
		CloseEastDoors();
	}
	if (bWestDoor) {
		CloseWestDoors();
	}
}