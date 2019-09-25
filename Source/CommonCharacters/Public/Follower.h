// Created by Francesco Corso. Labeled for reuse with attribution under Creative Commons.

#pragma once

#include "CoreMinimal.h"
#include "Followable.h"
#include "Follower.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
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
	 * Start following a given character
	 */
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "Followers")
	void StartFollowing(IFollowable* Character);

	/**
	 * Stop following a given character
	 */
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "Followers")
	void StopFollowing(IFollowable* Character);
	
};
