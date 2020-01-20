// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "ProceduralGridLevel.h"
#include "GameFramework/GameModeBase.h"
#include "IsaacCloneGameMode.generated.h"

UCLASS(MinimalAPI)
class AIsaacCloneGameMode : public AGameModeBase
{
	GENERATED_BODY()

	UPROPERTY(Category = Level, EditAnywhere)
	uint8 LEVEL_SIZE = 9;

	AProceduralGridLevel* GridLevel;

public:
	AIsaacCloneGameMode();

	void virtual BeginPlay() override;

	//uint8 GetLevelSize();

	//void SetLevelSize(uint8 size);
};



