// Fill out your copyright notice in the Description page of Project Settings.

#include "BasicRoom.h"

ABasicRoom::ABasicRoom() {
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	InitRoomMeshes();
}

// Called when the game starts or when spawned
void ABasicRoom::BeginPlay()
{
	Super::BeginPlay();

	// UStaticMeshComponent* UNorthDoor;
	// UStaticMeshComponent* UWestDoor;
	// UStaticMeshComponent* UEastDoor;
	// UStaticMeshComponent* USouthDoor;
}

void ABasicRoom::Tick(float DeltaTime)
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

void ABasicRoom::InitRoomMeshes() {
	URoomComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Basic Room"));
	URoomMesh = LoadObject<UStaticMesh>(nullptr, TEXT("StaticMesh'/Game/Level/Meshes/Basic_Room.Basic_Room'"));
	URoomComponent->SetStaticMesh(URoomMesh);
	URoomComponent->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepWorldTransform);

	FVector scale = FVector(24, 35, 5);
	BoxComponent->SetRelativeScale3D(scale);
}

// TODO: FINISH
//void ABasicRoom::OnOverlapBegin(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
//{
//	if (OtherActor->ActorHasTag(FName("Player"))) {
//		if (!bIsCleared) {
//			bPlayerEntered = true;
//			// UE_LOG(LogTemp, Warning, TEXT("PlayerEntered: %s"), *(bPlayerEntered ? TEXT("True") : TEXT("False")));
//			Enemies = EnemySpawner->SpawnEnemies();
//		}
//		// UE_LOG(LogTemp, Warning, TEXT("Player Entered"));
//	}
//	// UE_LOG(LogTemp, Warning, TEXT("%s Entered at : %s"), *OtherActor->GetName(), *this->GetName());
//}

//void ABasicRoom::CloseAllDoors()
//{
//	CloseNorthDoors();
//	CloseSouthDoors();
//	CloseEastDoors();
//	CloseWestDoors();
//}

void ABasicRoom::CloseNorthDoors()
{
	FTransform Transform;
	Transform.SetLocation(URoomComponent->GetSocketLocation(FName("NorthDoor")));
	DoorMesh->AddInstance(Transform);
}

void ABasicRoom::CloseSouthDoors()
{
	FTransform Transform;
	Transform.SetLocation(URoomComponent->GetSocketLocation(FName("SouthDoor")));
	DoorMesh->AddInstance(Transform);
}

void ABasicRoom::CloseWestDoors()
{
	FTransform Transform;
	Transform.SetLocation(URoomComponent->GetSocketLocation(FName("WestDoor")));
	DoorMesh->AddInstance(Transform);
}

void ABasicRoom::CloseEastDoors()
{
	FTransform Transform;
	Transform.SetLocation(URoomComponent->GetSocketLocation(FName("EastDoor")));
	DoorMesh->AddInstance(Transform);
}

void ABasicRoom::OpenDoorsOnClear()
{
	UE_LOG(LogTemp, Warning, TEXT("North: %s"), (bNorthDoor ? TEXT("True") : TEXT("False")));
	UE_LOG(LogTemp, Warning, TEXT("South: %s"), (bSouthDoor ? TEXT("True") : TEXT("False")));
	UE_LOG(LogTemp, Warning, TEXT("East: %s"), (bEastDoor ? TEXT("True") : TEXT("False")));
	UE_LOG(LogTemp, Warning, TEXT("West: %s"), (bWestDoor ? TEXT("True") : TEXT("False")));
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
