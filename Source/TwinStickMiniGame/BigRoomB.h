// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Room.h"
#include "BigRoomB.generated.h"

/**
 * 
 */
UCLASS()
class TWINSTICKMINIGAME_API ABigRoomB : public ARoom
{
	GENERATED_BODY()
	
public:
	ABigRoomB();

	virtual void Tick(float DeltaTime) override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void InitRoomMeshes() override;
	
	virtual void OnOverlapBegin(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult) override;
};
