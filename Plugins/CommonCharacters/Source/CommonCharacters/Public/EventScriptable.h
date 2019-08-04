// Created by Francesco Corso. Labeled for reuse with attribution under Creative Commons.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "WorldElement.h"
#include "EventScriptable.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UEventScriptable : public UWorldElement
{
	GENERATED_BODY()
};

/**
 * Interface that is used to represent an event script
 */
class COMMONCHARACTERS_API IEventScriptable : public IWorldElement
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	/**
	 * Trigger the event scripts of this object
	 */
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "Event Scripts")
	void TriggerEventScript();

};
