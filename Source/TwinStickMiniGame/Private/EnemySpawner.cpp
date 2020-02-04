

#include "EnemySpawner.h"
#include "Components/BillboardComponent.h"
#include "Components/BoxComponent.h"
#include "IsaacClonePawn.h"
#include "Engine/World.h"

// Sets default values for this component's properties
UEnemySpawner::UEnemySpawner()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("Spawn Volume"));
	// BoxComponent->SetCollisionProfileName(TEXT("OverlapAllDynamic"));
	// BoxComponent->ResetRelativeTransform();


	// BoxComponent->AttachToComponent(GetOwner()->GetRootComponent(), FAttachmentTransformRules::KeepRelativeTransform);
}


// Called when the game starts
void UEnemySpawner::BeginPlay()
{
	Super::BeginPlay();

	// BoxComponent->OnComponentBeginOverlap.AddDynamic(this, &UEnemySpawner::OnOverlapBegin);
	// ...
	
}


// Called every frame
void UEnemySpawner::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

TArray<AEnemyCharacter*>* UEnemySpawner::SpawnEnemies()
{
	// Array to hold all the enemies to return
	TArray<AEnemyCharacter*>* Enemies = new TArray<AEnemyCharacter*>();

	// Spawn a random amount of enemies
	uint8 NumberOfEnemies = FMath::RandRange(2, MaxNumberOfEnemies);
	for (int i = 0; i < NumberOfEnemies; i++) {
		FVector SpawnerExtent = BoxComponent->GetScaledBoxExtent();
		float RandomX = FMath::RandRange(-1 * SpawnerExtent.X, SpawnerExtent.X);
		float RandomY = FMath::RandRange(-1 * SpawnerExtent.Y, SpawnerExtent.Y);
		// float RandomZ = FMath::RandRange(-1 * SpawnerExtent.Z, SpawnerExtent.Z);
		FVector SpawnLocation = FVector(RandomX, RandomY, SpawnerExtent.Z + 80) + (GetOwner()->GetActorLocation());
		FActorSpawnParameters Params;
		Params.bNoFail = true;
		AEnemyCharacter* Enemy = GetWorld()->SpawnActor<AEnemyCharacter>(AEnemyCharacter::StaticClass(), SpawnLocation, FRotator::ZeroRotator, Params);

		// Add Enemy to the array of enemies for tracking
		Enemies->Add(Enemy);
	}
	return Enemies;
}

TArray<AEnemyCharacter*>* UEnemySpawner::SpawnBoss()
{
	return nullptr;
}

void UEnemySpawner::ScaleSpawnerVolume(FVector Extent)
{
	BoxComponent->SetRelativeScale3D(Extent);
	//UE_LOG(LogTemp, Warning, TEXT("Unscaled Extent: %s"), *BoxComponent->GetUnscaledBoxExtent().ToString());
	//UE_LOG(LogTemp, Warning, TEXT("Scaled Extent: %s"), *BoxComponent->GetScaledBoxExtent().ToString());
	//UE_LOG(LogTemp, Warning, TEXT("Scaled Extent: %s"), *BoxComponent->GetComponentScale().ToString());
}

void UEnemySpawner::SetMaxNumberOfEnemies(uint8 Enemies)
{
	MaxNumberOfEnemies = Enemies;
}

