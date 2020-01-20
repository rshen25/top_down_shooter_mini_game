

#pragma once

#include "CoreMinimal.h"
#include "EnemyCharacter.h"
#include "Components/ActorComponent.h"
#include "EnemySpawner.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class UEnemySpawner : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UEnemySpawner();

	UPROPERTY(Category = Spawner, EditAnywhere)
	uint8 MaxNumberOfEnemies = 7;

	UPROPERTY(EditAnywhere)
	class UBoxComponent* BoxComponent;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	TArray<AEnemyCharacter*>* SpawnEnemies();

	// TODO: Write function, create boss
	TArray<AEnemyCharacter*>* SpawnBoss();

	void ScaleSpawnerVolume(FVector Extent);
	
	void SetMaxNumberOfEnemies(uint8 Enemies);
};
