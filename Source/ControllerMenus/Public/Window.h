// Created by Francesco Corso. Labeled for reuse with attribution under Creative Commons.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "WindowBack.h"
#include "Window.generated.h"

/**
 * Primative structural class that serves as the basis for every window in the game.
 */
UCLASS(Blueprintable)
class CONTROLLERMENUS_API UWindow : public UUserWidget {
	GENERATED_BODY()

public:
	/**
	 * Serves as the background behind the window. Not all windows are required to have this element.
	 */
	UPROPERTY(BlueprintReadOnly, Category = Components, meta = (BindWidgetOptional))
	UWindowBack* WindowBack;

	/**
	 * Serves as the holder of the windows contents. This element is automatically sized based on the background.
	 */
	UPROPERTY(BlueprintReadOnly, Category = Components, meta = (BindWidget))
	UPanelWidget* ContentsPane;

protected:
	TSharedRef<SWidget> RebuildWidget() override;

    /**
    * Determines if the key that is currently pressed is mapped to the given action mapping
    * @param Key The key being pressed
    * @param Action The action binding
    * @return if the input is valid
    */
    UFUNCTION(BlueprintPure, Category = Input)
    virtual bool ValidInput(FKey Key, FName Action) const;
	
};
