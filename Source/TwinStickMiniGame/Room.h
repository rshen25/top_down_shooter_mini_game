// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnemySpawner.h"
#include "Engine/World.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/InstancedStaticMeshComponent.h"
#include "GameFramework/Actor.h"
#include "Room.generated.h"

UCLASS()
class TWINSTICKMINIGAME_API ARoom : public AActor
{
	GENERATED_BODY()
	
public:	

	// Door Meshes -------------------------
	UInstancedStaticMeshComponent* DoorMesh;

	// Door booleans, true if there is a door, false o.w.
	bool bNorthDoor = false;
	bool bSouthDoor = false;
	bool bWestDoor = false;
	bool bEastDoor = false;

	UPROPERTY(Category = Room, EditAnywhere)
	bool bPlayerEntered;

	UPROPERTY(Category = Room, EditAnywhere)
	bool bIsCleared;

	FVector2D FRoomCoords;

	UPROPERTY(Category = Spawner, EditAnywhere)
	class UEnemySpawner* EnemySpawner;

	UPROPERTY(EditAnywhere)
	class UBoxComponent* BoxComponent;

	// Sets default values for this actor's properties
	ARoom();

protected:
	TArray<AActor*> Enemies;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Rooms)
	UStaticMeshComponent* URoomComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Rooms)
	UStaticMesh* URoomMesh;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void InitRoomMeshes();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;	

	UFUNCTION(Category = Spawning)
	virtual void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	// Closes all the doors to the room upon player entering the room
	virtual void CloseAllDoors();

	// Close Doors
	virtual void CloseNorthDoors();
	virtual void CloseSouthDoors();
	virtual void CloseWestDoors();
	virtual void CloseEastDoors();

	// Opens the appropriate doors when the player as cleared the room
	virtual void OpenDoorsOnClear();
};
