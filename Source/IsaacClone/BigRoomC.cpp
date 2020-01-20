// Fill out your copyright notice in the Description page of Project Settings.

#include "BigRoomC.h"
ABigRoomC::ABigRoomC() 
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	InitRoomMeshes();
}

void ABigRoomC::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ABigRoomC::BeginPlay()
{
	Super::BeginPlay();
}

void ABigRoomC::InitRoomMeshes() {
	//USceneComponent* RootSceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
	//RootComponent = RootSceneComponent;

	URoomComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Big Room C"));
	URoomMesh = LoadObject<UStaticMesh>(nullptr, TEXT("StaticMesh'/Game/Level/Meshes/Big_Room_C.Big_Room_C'"));
	URoomComponent->SetStaticMesh(URoomMesh);
	URoomComponent->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
}

void ABigRoomC::OnOverlapBegin(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{

}


