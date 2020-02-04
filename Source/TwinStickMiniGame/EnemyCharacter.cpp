// Fill out your copyright notice in the Description page of Project Settings.

#include "EnemyCharacter.h"


// Sets default values
AEnemyCharacter::AEnemyCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	AIControllerClass = AEnemyPawnAIController::StaticClass();
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
	USkeletalMeshComponent* Mesh = GetMesh();
	USkeletalMesh* SkeletalMesh = LoadObject<USkeletalMesh>(nullptr, TEXT("SkeletalMesh'/Game/Mannequin/Character/Mesh/SK_Mannequin.SK_Mannequin'"));
	Mesh->SetSkeletalMesh(SkeletalMesh);
	Mesh->SetGenerateOverlapEvents(true);

	OverlapCapsule = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Overlap Capsule"));
	OverlapCapsule->AttachTo(RootComponent);
	//OverlapCapsule->AttachToComponent(Mesh, FAttachmentTransformRules::SnapToTargetIncludingScale);

	// TODO: Refactor hard-coded numbers
	OverlapCapsule->SetCapsuleRadius(22.0f);
	OverlapCapsule->SetCapsuleHalfHeight(44.0f);
	OverlapCapsule->SetRelativeScale3D(FVector(2.0, 2.0, 2.0));

	// Set walk speed
	UCharacterMovementComponent* MovementComponent = GetCharacterMovement();
	MovementComponent->MaxWalkSpeed = MovementComponent->MaxWalkSpeed * MoveSpeed;
	

	Tags.Add(FName("Enemy"));

	// TODO: Set Damage, MoveSpeed, etc, remove hardcoded numbers
	Damage = 20.0f;
}

// Called when the game starts or when spawned
void AEnemyCharacter::BeginPlay()
{
	Super::BeginPlay();

	OverlapCapsule->OnComponentBeginOverlap.AddDynamic(this, &AEnemyCharacter::OnOverlapBegin);
	// GetMesh()->OnComponentBeginOverlap.AddDynamic(this, &AEnemyCharacter::OnOverlapBegin);	
}

// Called every frame
void AEnemyCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AEnemyCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

float AEnemyCharacter::TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser)
{
	const float ActualDamage = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
	Health -= ActualDamage;
	// If Health is below 0, it dies
	if (Health <= 0) {
		Destroy();
	}
	return ActualDamage;
}

void AEnemyCharacter::OnOverlapBegin(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	if (OtherActor->ActorHasTag(FName("Player"))) {
		AIsaacClonePawn* Player = Cast<AIsaacClonePawn>(OtherActor);

		AController* Controller = Cast<AController>(GetController());
		if (Controller != nullptr && Player != nullptr) {
			// Damage Type
			TSubclassOf<UDamageType> const ValidDamageTypeClass = TSubclassOf<UDamageType>(UDamageType::StaticClass());
			FDamageEvent DamageEvent(ValidDamageTypeClass);
			Player->TakeDamage(Damage, DamageEvent, Controller, this);
		}
	}
}


// Setters ------------------------------------------------

void AEnemyCharacter::SetHealth(float health)
{
	Health = health;
}

void AEnemyCharacter::SetDamage(float damage)
{
	Damage = damage;
}

void AEnemyCharacter::SetMoveSpeed(float movespeed)
{
	MoveSpeed = movespeed;
}

void AEnemyCharacter::SetShotSpeed(float shotspeed)
{
	ShotSpeed = shotspeed;
}

// Getters ----------------------------------------------

float AEnemyCharacter::GetHealth()
{
	return Health;
}

float AEnemyCharacter::GetDamage()
{
	return Damage;
}

float AEnemyCharacter::GetMoveSpeed()
{
	return MoveSpeed;
}

float AEnemyCharacter::GetShotSpeed()
{
	return ShotSpeed;
}
