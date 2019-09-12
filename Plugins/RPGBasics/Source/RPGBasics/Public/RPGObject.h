// Created by Francesco Corso. Labeled for reuse with attribution under Creative Commons.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "RPGObject.generated.h"

/**
 * Basic object class that contains a few more additional functionalities
 */
UCLASS(abstract, Blueprintable, meta = (DisplayName = "RPG Object"))
class RPGBASICS_API URPGObject : public UObject {
	GENERATED_BODY()
	
public:
	void PostInitProperties() override;

	/**
	 * Initialize the object from the constructor
	 */
	UFUNCTION(BlueprintImplementableEvent, Category = Construction)
	void Initialize();

};
