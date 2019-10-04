// Created by Francesco Corso. Labeled for reuse with attribution under Creative Commons.

#pragma once

#include "CoreMinimal.h"
#include "WorldElement.h"
#include "Followable.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI, BlueprintType)
class UFollowable : public UWorldElement {
	GENERATED_BODY()
};

/**
 * 
 */
class COMMONCHARACTERS_API IFollowable : public IWorldElement {
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	
};
