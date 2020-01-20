// Fill out your copyright notice in the Description page of Project Settings.

#include "EmptyRoom.h"
AEmptyRoom::AEmptyRoom() 
{
	PrimaryActorTick.bCanEverTick = true;

	InitRoomMeshes();
}

void AEmptyRoom::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AEmptyRoom::BeginPlay()
{
	Super::BeginPlay();
}

void AEmptyRoom::InitRoomMeshes()
{
	// Default room is the empty room
	URoomComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Empty Room"));
	URoomMesh = LoadObject<UStaticMesh>(nullptr, TEXT("StaticMesh'/Game/Level/Meshes/Empty_Room.Empty_Room'"));
	URoomComponent->SetStaticMesh(URoomMesh);
	URoomComponent->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
}
