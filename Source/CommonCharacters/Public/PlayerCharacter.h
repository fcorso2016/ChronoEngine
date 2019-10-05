// Created by Francesco Corso. Labeled for reuse with attribution under Creative Commons.

#pragma once

#include "CoreMinimal.h"
#include "Followable.h"
#include "Camera/CameraComponent.h"
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

	/**
	 * Have the AI temporarily take control of the character for the purpose of events
	 * @return if the AI successfully takes control of the pawn
	 */
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "Movement")
	bool AI_PossessPawn();

	/**
	 * Have the player regain control of the pawn after the AI used it
	 * @return if the selected player successfully regains control
	 * @param PlayerIndex the index of the player that is regaining control
	 */
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "Movement")
	bool RegainControl(int PlayerIndex = 0);

};
