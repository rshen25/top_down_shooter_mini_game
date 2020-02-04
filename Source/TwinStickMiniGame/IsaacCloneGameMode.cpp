// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#include "IsaacCloneGameMode.h"
#include "DefaultPlayerController.h"
#include "IsaacClonePawn.h"

AIsaacCloneGameMode::AIsaacCloneGameMode()
{
	// set default pawn class to our character class
	DefaultPawnClass = AIsaacClonePawn::StaticClass();
	
	PlayerControllerClass = ADefaultPlayerController::StaticClass();
}

void AIsaacCloneGameMode::BeginPlay()
{
	Super::BeginPlay();

	FVector Loc = FVector(0, 0, 0);
	GridLevel = GetWorld()->SpawnActor<AProceduralGridLevel>(AProceduralGridLevel::StaticClass(), Loc, FRotator::ZeroRotator);
	//GridLevel->BeginPlay();
}

//uint8 AIsaacCloneGameMode::GetLevelSize()
//{
//	return LEVEL_SIZE;
//}
//
//void AIsaacCloneGameMode::SetLevelSize(uint8 size)
//{
//	LEVEL_SIZE = size;
//}
