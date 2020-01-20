// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Room.h"
#include "EmptyRoom.generated.h"

/**
 * 
 */
UCLASS()
class ISAACCLONE_API AEmptyRoom : public ARoom
{
	GENERATED_BODY()
	
public:
	AEmptyRoom();

	virtual void Tick(float DeltaTime) override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void InitRoomMeshes() override;
	
	
};
