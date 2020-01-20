
#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "EnemyPawnAIController.generated.h"

/**
 * 
 */
UCLASS()
class ISAACCLONE_API AEnemyPawnAIController : public AAIController
{
	GENERATED_BODY()

private:
	virtual void BeginPlay() override;
	
public:
	virtual void Tick(float DeltaTime) override;

	//UFUNCTION()
	//FVector GetPathToPlayer();

	UFUNCTION()
	void OnPossessedDeath();
};
