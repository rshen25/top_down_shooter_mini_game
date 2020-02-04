// Fill out your copyright notice in the Description page of Project Settings.

#include "BigRoomB.h"
ABigRoomB::ABigRoomB()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	InitRoomMeshes();
}

void ABigRoomB::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ABigRoomB::BeginPlay()
{
	Super::BeginPlay();
}

void ABigRoomB::InitRoomMeshes() {
	//USceneComponent* RootSceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
	//RootComponent = RootSceneComponent;

	URoomComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Big Room B"));
	URoomMesh = LoadObject<UStaticMesh>(nullptr, TEXT("StaticMesh'/Game/Level/Meshes/Big_Room_B.Big_Room_B'"));
	URoomComponent->SetStaticMesh(URoomMesh);
	URoomComponent->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
}

void ABigRoomB::OnOverlapBegin(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
}

