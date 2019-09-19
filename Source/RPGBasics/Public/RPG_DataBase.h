// Created by Francesco Corso. Labeled for reuse with attribution under Creative Commons.

#pragma once

#include "CoreMinimal.h"
#include "ValidatedDataAsset.h"
#include "RPG_DataBase.generated.h"

/**
 * Serves a the baseline class for the creation of RPG data assets
 */
UCLASS(Blueprintable)
class RPGBASICS_API URPG_DataBase : public UValidatedDataAsset {
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
	
};
