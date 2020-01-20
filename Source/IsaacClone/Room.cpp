// Fill out your copyright notice in the Description page of Project Settings.

#include "Room.h"

// Sets default values
ARoom::ARoom()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	bIsCleared = false;
	bPlayerEntered = false;

	USceneComponent* RootSceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
	RootComponent = RootSceneComponent;

	EnemySpawner = CreateDefaultSubobject<UEnemySpawner>(TEXT("Enemy Spawner"));

	BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("Spawn Volume"));

	BoxComponent->AttachTo(RootComponent);
	
	EnemySpawner->BoxComponent = BoxComponent;
	// BillboardComponent = CreateDefaultSubobject<UBillboardComponent>(TEXT("Billboard"));
	BoxComponent->SetCollisionProfileName(TEXT("Trigger"));
	BoxComponent->ResetRelativeTransform();

	// TODO: Load Doors
	DoorMesh = CreateDefaultSubobject<UInstancedStaticMeshComponent>(TEXT("DoorMeshInstance"));
	DoorMesh->SetStaticMesh(LoadObject<UStaticMesh>(nullptr, TEXT("StaticMesh'/Game/StarterContent/Shapes/Shape_WideCapsule.Shape_WideCapsule'")));
	//UWestDoor;
	//UEastDoor;
	//USouthDoor;
}

// Called when the game starts or when spawned
void ARoom::BeginPlay()
{
	Super::BeginPlay();

	BoxComponent->OnComponentBeginOverlap.AddDynamic(this, &ARoom::OnOverlapBegin);
}

void ARoom::InitRoomMeshes()
{
	// Default room is the empty room
	URoomComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Empty Room"));
	URoomMesh = LoadObject<UStaticMesh>(nullptr, TEXT("StaticMesh'/Game/Level/Meshes/Empty_Room.Empty_Room'"));
	URoomComponent->SetStaticMesh(URoomMesh);

	URoomComponent->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
}

// Called every frame
void ARoom::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ARoom::OnOverlapBegin(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	if (OtherActor->ActorHasTag(FName("Player"))) {
		if (!bIsCleared && !bPlayerEntered) {
			bPlayerEntered = true;
			CloseAllDoors();
			UE_LOG(LogTemp, Warning, TEXT("PlayerEntered: %s"), (bPlayerEntered ? TEXT("True") : TEXT("False")));
			EnemySpawner->SpawnEnemies();
		}
		// UE_LOG(LogTemp, Warning, TEXT("Player Entered"));
	}
	// UE_LOG(LogTemp, Warning, TEXT("%s Entered at : %s"), *OtherActor->GetName(), *this->GetName());
}

void ARoom::CloseAllDoors()
{
	CloseNorthDoors();
	CloseSouthDoors();
	CloseEastDoors();
	CloseWestDoors();
}

void ARoom::CloseNorthDoors()
{
	//FTransform Transform;
	//Transform.SetLocation(URoomComponent->GetSocketLocation(FName("NorthDoor")));
	//DoorMesh->AddInstance(Transform);
}

void ARoom::CloseSouthDoors()
{
	//FTransform Transform;
	//Transform.SetLocation(URoomComponent->GetSocketLocation(FName("SouthDoor")));
	//DoorMesh->AddInstance(Transform);
}

void ARoom::CloseWestDoors()
{
	//FTransform Transform;
	//Transform.SetLocation(URoomComponent->GetSocketLocation(FName("WestDoor")));
	//DoorMesh->AddInstance(Transform);
}

void ARoom::CloseEastDoors()
{
	//FTransform Transform;
	//Transform.SetLocation(URoomComponent->GetSocketLocation(FName("EastDoor")));
	//DoorMesh->AddInstance(Transform);
}


void ARoom::OpenDoorsOnClear()
{
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




