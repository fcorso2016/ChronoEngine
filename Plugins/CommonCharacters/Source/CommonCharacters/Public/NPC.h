// Created by Francesco Corso. Labeled for reuse with attribution under Creative Commons.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "EventScriptable.h"
#include "NPC.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UNPC : public UEventScriptable {
	GENERATED_BODY()
};

/**
 * Represents an NPC within the game
 */
class COMMONCHARACTERS_API INPC : public IEventScriptable {
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:

};
