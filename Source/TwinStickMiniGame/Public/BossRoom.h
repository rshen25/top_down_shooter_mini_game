

#pragma once

#include "CoreMinimal.h"
#include "Room.h"
#include "BossRoom.generated.h"

/**
 * 
 */
UCLASS()
class TWINSTICKMINIGAME_API ABossRoom : public ARoom
{
	GENERATED_BODY()

public:
	ABossRoom();

	virtual void Tick(float DeltaTime) override;
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void InitRoomMeshes() override;

	virtual void OnOverlapBegin(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult) override;
	
};
