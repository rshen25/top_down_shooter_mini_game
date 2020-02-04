// Fill out your copyright notice in the Description page of Project Settings.

#include "BigRoomD.h"
ABigRoomD::ABigRoomD()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	InitRoomMeshes();
}

void ABigRoomD::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ABigRoomD::BeginPlay()
{
	Super::BeginPlay();
}

void ABigRoomD::InitRoomMeshes() {
	//USceneComponent* RootSceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
	//RootComponent = RootSceneComponent;

	URoomComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Big Room D"));
	URoomMesh = LoadObject<UStaticMesh>(nullptr, TEXT("StaticMesh'/Game/Level/Meshes/Big_Room_D.Big_Room_D'"));
	URoomComponent->SetStaticMesh(URoomMesh);
	URoomComponent->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
}

void ABigRoomD::OnOverlapBegin(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{

}


