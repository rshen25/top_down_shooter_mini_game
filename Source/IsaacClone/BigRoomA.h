// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Room.h"
#include "BigRoomA.generated.h"

/**
 * 
 */
UCLASS()
class ISAACCLONE_API ABigRoomA : public ARoom
{
	GENERATED_BODY()

public:
	ABigRoomA();

	virtual void Tick(float DeltaTime) override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void InitRoomMeshes() override;

	//virtual void OnOverlapBegin(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult) override;

	// Closes all the doors to the room upon player entering the room
	virtual void CloseAllDoors() override;

	virtual void CloseNorthDoors() override;
	virtual void CloseSouthDoors() override;
	virtual void CloseWestDoors() override;
	virtual void CloseEastDoors() override;

	// Opens the appropriate doors when the player as cleared the room
	virtual void OpenDoorsOnClear() override;
};
