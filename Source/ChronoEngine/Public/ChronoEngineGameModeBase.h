// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "ChronoWorldSettings.h"
#include "ChronoEngineGameModeBase.generated.h"

/**
 * The game mode used to as the basis for the framework
 */
UCLASS()
class CHRONOENGINE_API AChronoEngineGameModeBase : public AGameModeBase {
	GENERATED_BODY()

protected:
	/**
	 * Retrieves the world settings for the game
	 */
	UFUNCTION(BlueprintPure, Category = "World")
	FName GetDebugStartMap() const;
	
};
