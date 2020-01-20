
#include "EnemyPawn.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/PawnMovementComponent.h"
#include "GameFramework/FloatingPawnMovement.h"

// Sets default values
AEnemyPawn::AEnemyPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	AIControllerClass = AEnemyPawnAIController::StaticClass();

	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Static Mesh"));
	UStaticMesh* Mesh = LoadObject<UStaticMesh>(nullptr, TEXT("StaticMesh'/Engine/BasicShapes/Sphere.Sphere'"));
	StaticMeshComponent->SetStaticMesh(Mesh);

	PawnMovementComponent = CreateDefaultSubobject<UFloatingPawnMovement>(TEXT("Movement Component"));
	//PawnMovementComponent->MaxSpeed = MoveSpeed;
	//PawnMovementComponent->Acceleration = 1.0f;
	PawnMovementComponent->ConstrainDirectionToPlane(FVector(0, 0, 130));
	PawnMovementComponent->ConstrainLocationToPlane(FVector(0, 0, 130));
}

// Called when the game starts or when spawned
void AEnemyPawn::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AEnemyPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AEnemyPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AEnemyPawn::MoveDirection(FVector direction)
{

}

// Setters ------------------------------------------------

void AEnemyPawn::SetHealth(float health)
{
	Health = health;
}

void AEnemyPawn::SetDamage(float damage)
{
	Damage = damage;
}

void AEnemyPawn::SetMoveSpeed(float movespeed)
{
	MoveSpeed = movespeed;
}

void AEnemyPawn::SetShotSpeed(float shotspeed)
{
	ShotSpeed = shotspeed;
}

// Getters ----------------------------------------------

float AEnemyPawn::GetHealth()
{
	return Health;
}

float AEnemyPawn::GetDamage()
{
	return Damage;
}

float AEnemyPawn::GetMoveSpeed()
{
	return MoveSpeed;
}

float AEnemyPawn::GetShotSpeed()
{
	return ShotSpeed;
}



