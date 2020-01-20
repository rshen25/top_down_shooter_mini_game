// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "IsaacClonePawn.h"
#include "EnemyPawnAIController.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Engine/EngineTypes.h"
#include "GameFramework/DamageType.h"
#include "Components/SkeletalMeshComponent.h"
#include "GameFramework/Character.h"
#include "EnemyCharacter.generated.h"

UCLASS()
class ISAACCLONE_API AEnemyCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AEnemyCharacter();

	UCapsuleComponent* OverlapCapsule;

	// Basic Enemy stats such as health, movespeed, damage, etc ---------------
	UPROPERTY(Category = Stats, EditAnywhere)
	float Health = 100.0f;

	UPROPERTY(Category = Stats, EditAnywhere)
	float Damage;

	UPROPERTY(Category = Stats, EditAnywhere)
	float MoveSpeed = 0.5f;

	UPROPERTY(Category = Stats, EditAnywhere)
	float ShotSpeed;

	UPROPERTY(Category = Stats, EditAnywhere)
	bool bCanFly;

	UPROPERTY(Category = Stats, EditAnywhere)
	bool bCanFire;
	// END --------------------------------------------------------------------

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// Called when the character takes damage from a damage source
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;

	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);

	// Setters ----------------------------------------------------------------
	void SetHealth(float health);

	void SetDamage(float damage);

	void SetMoveSpeed(float movespeed);

	void SetShotSpeed(float shotspeed);


	// Getters ---------------------------------------------------------------
	float GetHealth();

	float GetDamage();

	float GetMoveSpeed();

	float GetShotSpeed();
	
};
