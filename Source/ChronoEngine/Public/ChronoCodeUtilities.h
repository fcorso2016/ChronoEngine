// Created by Francesco Corso. Labeled for reuse with attribution under Creative Commons.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "ChronoCodeUtilities.generated.h"

/**
 * A basic class used to hold basic game functions that cannot be implemented in Blueprints
 */
UCLASS()
class UChronoCodeUtilities : public UBlueprintFunctionLibrary {
	GENERATED_BODY()

public:
	/**
	 * Retrieve an enemy name suffix based on the number of possible enemies
	 */
	UFUNCTION(BlueprintPure, Category = "Utilities|Text")
	static FText GetSuffixFromIndex(int Index);
	
};

