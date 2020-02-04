

#pragma once

#include "CoreMinimal.h"
#include "EnemyPawnAIController.h"
#include "GameFramework/Pawn.h"
#include "EnemyPawn.generated.h"

UCLASS()
class TWINSTICKMINIGAME_API AEnemyPawn : public APawn
{
	GENERATED_BODY()

	UPROPERTY(Category = Mesh, VisibleDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class UStaticMeshComponent* StaticMeshComponent;

	UPROPERTY(Category = Movement, EditAnywhere, meta = (AllowPrivateAccess = "true"))
	class UFloatingPawnMovement* PawnMovementComponent;

public:
	// Sets default values for this pawn's properties
	AEnemyPawn();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Basic Enemy stats such as health, movespeed, damage, etc ---------------
	UPROPERTY(Category = Stats, EditAnywhere)
		float Health = 100.0f;

	UPROPERTY(Category = Stats, EditAnywhere)
		float Damage;

	UPROPERTY(Category = Stats, EditAnywhere)
		float MoveSpeed = 100.0f;

	UPROPERTY(Category = Stats, EditAnywhere)
		float ShotSpeed;

	UPROPERTY(Category = Stats, EditAnywhere)
		bool bCanFly;

	UPROPERTY(Category = Stats, EditAnywhere)
		bool bCanFire;
	// END --------------------------------------------------------------------

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void MoveDirection(FVector direction);

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


	// TODO: May not need these
	//bool isAbleToFly();
	//bool isAbleToFire();
	
};
