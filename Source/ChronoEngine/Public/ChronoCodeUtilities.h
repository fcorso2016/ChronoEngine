// Created by Francesco Corso. Labeled for reuse with attribution under Creative Commons.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "ChronoCodeUtilities.generated.h"

UENUM(BlueprintType)
enum class EControlMode : uint8 {
	None			UMETA(DisplayName = "None"),
	GameAndUI		UMETA(DisplayName = "Game and UI"),
	UIOnly			UMETA(DisplayName = "UI Only"),
	GameOnly		UMETA(DisplayName = "Game Only")
};

/**
 * A basic class used to hold basic game functions that cannot be implemented in Blueprints
 */
UCLASS()
class UChronoCodeUtilities : public UBlueprintFunctionLibrary {
	GENERATED_BODY()

public:
	/**
	 * Retrieve an enemy name suffix based on the number of possible enemies
	 * @return the textual suffix
	 * @param Index the index of the enemy
	 */
	UFUNCTION(BlueprintPure, Category = "Utilities|Text")
	static FText GetSuffixFromIndex(int Index);

	/**
	 * Get the current view mode of the controller
	 * 
	 * Written by user G_t_Pianoman on the Unreal Engine Forums
	 * Link: https://forums.unrealengine.com/unreal-engine/feedback-for-epic/54702-get-input-mode-node
	 * @return if the type on input the game accepts
	 * @param PlayerController the player controller in questions
	 */
	UFUNCTION(BlueprintPure, Category = "Runtime Inspector")
	static EControlMode GetCurrentViewMode(const APlayerController* PlayerController);

	/**
	 * Get the value of an invalid index
	 * @return the value of INDEX_NONE
	 */
	UFUNCTION(BlueprintPure, Category = "Utilities|Arrays")
	static int GetNullIndex();
	
};

