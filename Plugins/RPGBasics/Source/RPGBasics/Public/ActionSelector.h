// Created by Francesco Corso. Labeled for reuse with attribution under Creative Commons.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "ActionSelector.generated.h"

/**
 * A delegate that is triggered when a response is ready
 */
DECLARE_DYNAMIC_DELEGATE_OneParam(FOnInputComplete, UObject*, Selection);

// This class does not need to be modified.
UINTERFACE(MinimalAPI, BlueprintType)
class UActionSelector : public UInterface {
	GENERATED_BODY()
};

/**
 * An interface that is used for objects that accept input from the UI
 */
class RPGBASICS_API IActionSelector {
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	/**
	 * Prompt for a selection and what for a response
	 * @param OnInputComplete The event triggered when the response is made
	 * @param Object An object that is passed through for usage by the reciever
	 */
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = Input)
	void SelectAction(const FOnInputComplete& OnInputComplete, UObject* Object);
	
};
