// Fill out your copyright notice in the Description page of Project Settings.

#include "MainCharacter.h"
#include "Components/InputComponent.h"
#include "Kismet/GameplayStatics.h"

AMainCharacter::AMainCharacter() {
	PrimaryActorTick.bCanEverTick = true;
	moveSpeed = 100.0;
}

void AMainCharacter::Tick(float DeltaSeconds)
{
}

void AMainCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) {
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// Set up player movement bindings
	PlayerInputComponent->BindAxis("MoveForward", this, &AMainCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AMainCharacter::MoveRight);
}

void AMainCharacter::MoveForward(float pValue)
{
	FVector Direction = FRotationMatrix(Controller->GetControlRotation()).GetScaledAxis(EAxis::X);
}

void AMainCharacter::MoveRight(float pValue)
{
}

float AMainCharacter::GetMoveSpeed()
{
	return moveSpeed;
}

void AMainCharacter::SetMoveSpeed()
{
}

void AMainCharacter::FireShot(FVector FireDirection)
{
}


