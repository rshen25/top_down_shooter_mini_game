

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "DefaultPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class ISAACCLONE_API ADefaultPlayerController : public APlayerController
{
	GENERATED_BODY()
	
	
public:
	ADefaultPlayerController();
	
	FVector2D PlayerCoords;
};
