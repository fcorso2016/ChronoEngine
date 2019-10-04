// Created by Francesco Corso. Labeled for reuse with attribution under Creative Commons.

#pragma once

#include "CoreMinimal.h"
#include "Followable.h"
#include "Follower.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI, BlueprintType)
class UFollower : public UFollowable {
	GENERATED_BODY()
};

/**
 * 
 */
class COMMONCHARACTERS_API IFollower : public IFollowable {
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	/**
	 * Set the home location of the character to your current location
	 */
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "Followers")
	void SetHomeLocation();

	/**
	 * Set the home location of the character to a specific position
	 * @param Location the location to set to
	 */
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "Followers")
	void SpecifyHomeLocation(FVector Location);
	
	/**
	 * Start following a given character
	 * @param Character the character to start following
	 */
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "Followers")
	void StartFollowing(const TScriptInterface<IFollowable>& Character);

	/**
	 * Stop following the designated character given character
	 */
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "Followers")
	void StopFollowing();

	/**
	 * Get the character tht is being followed
	 * @return the pawn that is being followed
	 */
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "Followers")
	const TScriptInterface<IFollowable> RetrievedFollowedCharacter();
	
};
