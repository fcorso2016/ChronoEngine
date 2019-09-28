// Created by Francesco Corso. Labeled for reuse with attribution under Creative Commons.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "WorldElement.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI, BlueprintType)
class UWorldElement : public UInterface {
	GENERATED_BODY()
};

/**
 * Represents an element within the game world
 */
class COMMONCHARACTERS_API IWorldElement {
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
};
