// Created by Francesco Corso. Labeled for reuse with attribution under Creative Commons.

#pragma once

#include "CoreMinimal.h"
#include "Window.h"
#include "Runtime/UMG/Public/Components/ScrollBox.h"
#include "HelpWindow.generated.h"

/**
 * A window that contains help information for the player to view
 */
UCLASS(Blueprintable)
class CONTROLLERMENUS_API UHelpWindow : public UWindow {
	GENERATED_BODY()

public:
    /**
     * The section of the window where the selectable options exist
     */
    UPROPERTY(BlueprintReadOnly, Category = Components, meta = (BindWidgetOptional))
    UScrollBox* ScrollableSection;

protected:
    TSharedRef<SWidget> RebuildWidget() override;

public:
    /**
     * Scroll the window by the specified amount
     * @param Scroll the amount to scroll the window by
     */
    UFUNCTION(BlueprintCallable, Category = Input)
    void ScrollWindow(float Scroll);

};
