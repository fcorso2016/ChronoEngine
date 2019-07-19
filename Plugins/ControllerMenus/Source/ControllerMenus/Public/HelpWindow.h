// Created by Francesco Corso. Labeled for reuse with attribution under Creative Commons.

#pragma once

#include "CoreMinimal.h"
#include "Window.h"
#include "Runtime/UMG/Public/Components/ScrollBox.h"
#include "HelpWindow.generated.h"

USTRUCT(BlueprintType)
struct FScrollActions {
    GENERATED_BODY()

public:
    /**
     * Scroll the scrolling domain up
     */
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
    FName ScrollUp;

    /**
     * Scroll the scrolling domain up
     */
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
    FName ScrollDown;

};

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

private:
    /**
     * List of all input mappings
     */
    UPROPERTY(EditAnywhere, Category = Input)
    FScrollActions WindowInputMappings;

public:
    UHelpWindow(const FObjectInitializer& ObjectInitializer);

protected:
    TSharedRef<SWidget> RebuildWidget() override;

    FReply NativeOnKeyDown(const FGeometry& MyGeometry, const FKeyEvent& InKeyEvent) override;

};
