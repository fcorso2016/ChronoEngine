// Created by cygon and IridiumStudios on the Unreal Engine forums.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "Components/TextBlock.h"
#include "FontHelper.generated.h"

/**
 * 
 */
UCLASS()
class CONTROLLERMENUS_API UFontHelper : public UBlueprintFunctionLibrary {
	GENERATED_BODY()

public:
	/**
	 * Measure the width of the string
	 * @param TextBlock The Text block to place the string in
	 * @param Text The string to be inserted
	 * @return The size of the Text to be added
	 */
	UFUNCTION(BlueprintPure, Category = Messages)
	static FVector2D MeasureString(UTextBlock* TextBlock, const FString& Text);

	/**
	 * Measure the width of the string
	 * @param TextBlock The text block to place the string in
	 * @param Text The string to be inserted
	 * @param WrapWidth The width of the text when it is wrapped
	 * @param LinePercentageHeight The height of the line
	 * @return The size of the text to be added
	 */
	UFUNCTION(BlueprintPure, Category = Messages)
	static FVector2D MeasureWrappedString(UTextBlock* TextBlock, const FString& Text, float WrapWidth, float LinePercentageHeight);
	
};
