// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PaperCharacter.h"
#include "MainCharacter.generated.h"

/**
 * The Main Character that the player controls
 */
UCLASS()
class ISAACCLONE_API AMainCharacter : public APaperCharacter
{
	GENERATED_BODY()

public:
	AMainCharacter();

protected:
	UPROPERTY(Category = Movement, EditAnywhere, BlueprintReadWrite)
	float moveSpeed;
	
public:
	UPROPERTY(Category = Movement, EditAnywhere, BlueprintReadWrite)
	float health;

	UPROPERTY(Category = Shooting, EditAnywhere, BlueprintReadWrite)
	float damage;

	UPROPERTY(Category = Shooting, EditAnywhere, BlueprintReadWrite)
	float fireRate;

	UPROPERTY(Category = Shooting, EditAnywhere, BlueprintReadWrite)
	float shotSpeed;

	UPROPERTY(Category = Shooting, EditAnywhere, BlueprintReadWrite)
	float range;

	virtual void Tick(float DeltaSeconds) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION(Category = Movement, BlueprintCallable)
	void MoveForward(float pValue);

	UFUNCTION(Category = Movement, BlueprintCallable)
	void MoveRight(float pValue);

	UFUNCTION(Category = Movement, BlueprintCallable)
	float GetMoveSpeed();

	UFUNCTION(Category = Movement, BlueprintCallable)
	void SetMoveSpeed();
	
	UFUNCTION(Category = Gameplay, BlueprintCallable)
	void FireShot(FVector FireDirection);
	
};
