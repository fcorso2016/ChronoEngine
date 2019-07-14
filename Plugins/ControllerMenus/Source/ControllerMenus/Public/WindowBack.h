// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "WindowBack.generated.h"

/**
 * Basic identifier class for UI elements that serve as the background to a window.
 */
UCLASS()
class CONTROLLERMENUS_API UWindowBack : public UUserWidget {
	GENERATED_BODY()

public:
	UWindowBack(const FObjectInitializer& ObjectInitializer);

protected:
	/**
	 * The amount of space between the edge of the window and the start of the window's contents.
	 */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Layout)
	FMargin FramePadding;
	
};
