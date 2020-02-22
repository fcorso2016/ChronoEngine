// Created by Francesco Corso. Labeled for reuse with attribution under Creative Commons.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/WorldSettings.h"
#include "ChronoWorldSettings.generated.h"

/**
 * The world settings used by the game in order to determine default starting maps for testing purposes
 */
UCLASS()
class CHRONOENGINE_API AChronoWorldSettings : public AWorldSettings {
	GENERATED_BODY()

public:
	/**
	 * The first map to load when launching a playtest from the editor
	 */
	UPROPERTY(EditAnywhere, Category = World)
	FName DebugStartMap;
	
};
