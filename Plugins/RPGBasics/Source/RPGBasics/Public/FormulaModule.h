// Created by Francesco Corso. Labeled for reuse with attribution under Creative Commons.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "FormulaModule.generated.h"

/**
 * A basic class used only for the processing of formulas for an attack
 */
UCLASS(Abstract, Blueprintable)
class RPGBASICS_API UFormulaModule : public UObject {
	GENERATED_BODY()

public:
	/**
	 * Compute the damage based on various input data
	 * @return the amount of damage to be dealt
	 * @param InputValues any formula variables needed for the calculation
	 */
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = "Battle Math")
	int ComputeDamage(const TMap<FName, float>& InputValues);

	/**
	 * Constructs a formula module class for usage in a calculation
	 * @return the constructed module
	 * @param Outer the object that called the construction algorithm
	 * @param ModuleClass the subclass being constructed
	 */
	UFUNCTION(BlueprintCallable, Category = "Object Construction")
	static UFormulaModule* ConstructFormulaModule(UObject* Outer, TSubclassOf<UFormulaModule> ModuleClass);
	
	
};
