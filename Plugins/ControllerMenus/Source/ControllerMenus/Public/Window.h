// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "WindowBack.h"
#include "Window.generated.h"

/**
 * Primative structural class that serves as the basis for every window in the game.
 */
UCLASS()
class CONTROLLERMENUS_API UWindow : public UUserWidget {
	GENERATED_BODY()

protected:
	/**
	 * Serves as the background behind the window. Not all windows are required to have this element.
	 */
	UPROPERTY(BlueprintReadOnly, Category = Components, meta = (BindWidget, OptionalWidget = true))
	UWindowBack* WindowBack;

	TSharedRef <SWidget> RebuildWidget() override;
	
};
