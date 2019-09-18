// Created by Francesco Corso. Labeled for reuse with attribution under Creative Commons.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "RPG_DataBase.generated.h"

/**
 * Serves a the baseline class for the creation of RPG data assets
 */
UCLASS(Blueprintable)
class RPGBASICS_API URPG_DataBase : public UPrimaryDataAsset {
	GENERATED_BODY()

public:
	/**
	 * The name of the object as seen by the player
	 */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Basic)
	FText Name;

	/**
	 * The textual description of the object to be displayed to the player
	 */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Basic)
	FText Description;

	void PostEditChangeProperty(struct FPropertyChangedEvent& PropertyChangedEvent) override;

	/**
	 * Called to validate the contents of the object and correct anything that is not possible
	 */
	UFUNCTION(BlueprintImplementableEvent, Category = Initialization)
	void ValidatePropertyInformation();
	
};
