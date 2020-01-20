// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Room.h"
#include "BigRoomC.generated.h"

/**
 * 
 */
UCLASS()
class ISAACCLONE_API ABigRoomC : public ARoom
{
	GENERATED_BODY()
	
public:
	ABigRoomC();

	virtual void Tick(float DeltaTime) override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void InitRoomMeshes() override;
	
	virtual void OnOverlapBegin(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult) override;
};
