

#include "EnemyPawnAIController.h"

void AEnemyPawnAIController::BeginPlay()
{
	Super::BeginPlay();
}

void AEnemyPawnAIController::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);
	
		auto PlayerPawn = GetWorld()->GetFirstPlayerController()->GetPawn();
		if (!ensure(PlayerPawn)) {
			// UE_LOG(LogTemp, Warning, TEXT("PlayerPawn not found"));
			return;
		}
		else {
			FString name = PlayerPawn->GetName();
			// UE_LOG(LogTemp, Warning, TEXT("PlayerPawn found: %s"), *name);
		}

		MoveToActor(PlayerPawn, 1.0f, true, true, true, 0, true);
		uint8 status = GetMoveStatus();
		// UE_LOG(LogTemp, Warning, TEXT("Status: %d"), status);
}

void AEnemyPawnAIController::OnPossessedDeath()
{
	if (!GetPawn()) {
		return;
	}
	else {
		GetPawn()->DetachFromControllerPendingDestroy();
	}
}

