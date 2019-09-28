// Created by Francesco Corso. Labeled for reuse with attribution under Creative Commons.

#pragma once

#include "CoreMinimal.h"
#include "Followable.h"
#include "PlayerCharacter.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI, BlueprintType)
class UPlayerCharacter : public UFollowable {
	GENERATED_BODY()
};

/**
 * Represents a player character in the game
 */
class COMMONCHARACTERS_API IPlayerCharacter : public IFollowable {
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	/**
	 * Get the set of events directly in front of the character
	 */
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "Event Scripts")
	void CheckForFrontEvents();

	/**
	 * Spawns any necessary follower characters behind the player in a chain
	 */
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "Followers")
	void SpawnFollowers();

};
