// Created by Francesco Corso. Labeled for reuse with attribution under Creative Commons.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "WindowBack.generated.h"

/**
 * Basic identifier class for UI elements that serve as the background to a window.
 */
UCLASS(Blueprintable)
class CONTROLLERMENUS_API UWindowBack : public UUserWidget {
	GENERATED_BODY()

protected:
	/**
	 * The amount of space between the edge of the window and the start of the window's contents.
	 */
	UPROPERTY(EditDefaultsOnly, Category = Layout)
	FMargin FramePadding;
	
public:
	UWindowBack(const FObjectInitializer& ObjectInitializer);

	/**
	 * Get the padding of the frame
	 * @return The amount of space between the edge of the window and the start of the window's contents.
	 */
	UFUNCTION(BlueprintPure, Category = Layout)
	const FMargin& GetFramePadding() const;
	
};
