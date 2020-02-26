// Created by Francesco Corso. Labeled for reuse with attribution under Creative Commons.

#pragma once

#include "CoreMinimal.h"
#include "Camera/PlayerCameraManager.h"
#include "ChronoCameraManager.generated.h"

/**
 * 
 */
UCLASS(BlueprintType)
class CHRONOENGINE_API AChronoCameraManager : public APlayerCameraManager {
	GENERATED_BODY()

private:
	/**
	 * The pawn being used by this class to set the camera info
	 */
	UPROPERTY()
	APawn* PlayerCharacter;

public:
	/**
	 * Set the player character used by this class
	 * @param NewPlayer the pawn to get information from
	 */
	UFUNCTION(BlueprintCallable, Category = Camera)
	void SetPlayerCharacter(APawn* NewPlayer);
	
};
