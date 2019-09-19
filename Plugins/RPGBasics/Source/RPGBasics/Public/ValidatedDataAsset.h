// Created by Francesco Corso. Labeled for reuse with attribution under Creative Commons.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "ValidatedDataAsset.generated.h"

/**
 * A basic data asset that can have its values validated by the game
 */
UCLASS(Blueprintable)
class RPGBASICS_API UValidatedDataAsset : public UPrimaryDataAsset {
	GENERATED_BODY()
	
public:
	void PostEditChangeProperty(struct FPropertyChangedEvent& PropertyChangedEvent) override;

	/**
	 * Called to validate the contents of the object and correct anything that is not possible
	 */
	UFUNCTION(BlueprintImplementableEvent, Category = Initialization)
	void ValidatePropertyInformation();
	
};
