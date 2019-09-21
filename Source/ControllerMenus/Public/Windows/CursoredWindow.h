// Created by Francesco Corso. Labeled for reuse with attribution under Creative Commons.

#pragma once

#include "CoreMinimal.h"
#include "Window.h"
#include "Primatives/Cursor.h"
#include "Runtime/UMG/Public/Components/ScrollBox.h"
#include "SelectableOption.h"
#include "ScrollWindow.h"
#include "CursoredWindow.generated.h"

/**
* Struct that stores the input handlers for the window
*/
USTRUCT(BlueprintType)
struct FCursorActions {
	GENERATED_BODY()

public:
	/** 
	 * The Up Input 
	 */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	FName UpInput;

	/** 
	 * The Down Input 
	 */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	FName DownInput;

	/**
	 * The Left Input 
	 */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	FName LeftInput;

	/** 
	 * The Right Input 
	 */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	FName RightInput;

	/**
	 * The Confirm Input
	 */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	FName ConfirmInput;

	/**
	 * The Cancel Input 
	 */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	FName CancelInput;

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
 * Delegate for when the user presses confirm 
 */
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FProcessConfirm, int, Index, FName, SelectionSymbol);

/**
 * Delegate for when the user presses cancel
 */
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FProcessCancel);

/**
 * A window containing a navigable interface that is under player control
 */
UCLASS(Blueprintable)
class CONTROLLERMENUS_API UCursoredWindow : public UWindow {
	GENERATED_BODY()

public:
	/**
	 * The section of the window where the selectable options exist
	 */
	UPROPERTY(BlueprintReadOnly, Category = Components, meta = (BindWidget))
	UPanelWidget* SelectionArea;

    /**
     * The section of the window where the selectable options exist
     */
    UPROPERTY(BlueprintReadOnly, Category = Components, meta = (BindWidgetOptional))
    UScrollBox* ScrollZone;

	/**
	 * List of all input mappings 
	 */
	UPROPERTY(BlueprintReadOnly, Category = Components, meta = (BindWidget))
	UCursor* WindowCursor;

	/**
	 * The list of elements in the window's layout
	 */
	UPROPERTY(BlueprintReadOnly, Category = Components)
	TArray<USelectableOption*> Elements;

private:
	/** 
	 * List of all input mappings
	 */
	UPROPERTY(EditAnywhere, Category = Input)
	FCursorActions WindowInputMappings;

	/**
	 * The horizontal alignment of the elements in the window
	 */
	UPROPERTY(EditAnywhere, Category = Window)
	TEnumAsByte<EHorizontalAlignment> HorizontalAlignment;

	/**
	 * The vertical alignment of the elements in the window 
	 */
	UPROPERTY(EditAnywhere, Category = Window)
	TEnumAsByte<EVerticalAlignment> VerticalAlignment;

	/**
	 * The index of the cursor in the window
	 */
	UPROPERTY(EditAnywhere, Category = Input, meta = (UIMin = -1, ClampMin = -1))
	int Index;

	/**
	 * Get the window's activation status 
	 */
	UPROPERTY(EditAnywhere, Category = Input)
	bool bIsActive;

public:
	/**
	 * The delegate called when the player presses confirm/clicks on an option
	 */
	UPROPERTY(BlueprintAssignable, Category = Input)
	FProcessConfirm OnConfirm;

	/**
	 * The delegate called when the player cancels out of the window
	 */
	UPROPERTY(BlueprintAssignable, Category = Input)
	FProcessCancel OnCancel;

	/**
	 * The help window for the game to display content based upon what the game needs it to contain
	 */
	UPROPERTY(BlueprintReadOnly, Category = Help)
	UScrollWindow* HelpWindow;
	
	UCursoredWindow(const FObjectInitializer& ObjectInitializer);

protected:
	TSharedRef<SWidget> RebuildWidget() override;

	void NativeConstruct() override;

public:
	/**
	 * Get the index of the cursor
	 * @return The index of the cursor in the window
	 */
	UFUNCTION(BlueprintPure, Category = Input)
	int GetIndex() const;

	/**
	 * Select a certain index of the window
	 * @param NewIndex The index to select
	 */
	UFUNCTION(BlueprintCallable, Category = Input)
	void Select(int NewIndex);

	/**
	 * Selects the specified element in the window
	 */
	void Select(USelectableOption* Option);

	/**
	 * Deselect the window, hiding the cursor
	 */
	UFUNCTION(BlueprintCallable, Category = Input)
	void Deselect();

	/**
	* Get if the window is active
	* @return The activation status of the window
	*/
	UFUNCTION(BlueprintPure, Category = Window)
	bool GetActive() const;

	/**
	* Set the window as active or not
	* @param bActive - The new activation status of the window
	*/
	UFUNCTION(BlueprintCallable, Category = Window)
	void SetActive(bool bActive);

	/**
	 * Sets the help window associated with this widget
	 * @param NewHelpWindow the new help window the be assigned
	 */
	UFUNCTION(BlueprintCallable, Category = Help)
	void SetHelpWindow(UScrollWindow* NewHelpWindow);

protected:
	/**
	 * Update the help window with information based on what the subwindow needs
	 */
	UFUNCTION(BlueprintImplementableEvent, Category = Help)
	void UpdateHelp();

private:
	/**
	 * Sets the position of the cursor in the window
	 */
	UFUNCTION()
	void SetCursorPosition();

	/**
	 * Creates an element and adds it to the window
	 * @param NewIndex the index of the element to add
	 */
	UFUNCTION()
	void AddElement(int NewIndex);

protected:
	/**
	 * Actually construct the new element and add it to the window
	 * @param NewIndex the index of element to construct
	 * @return The constructed element
	 */
	UFUNCTION(BlueprintImplementableEvent, Category = Window)
	USelectableOption* CreateNewElement(int NewIndex);

public:
	/**
	 * Gets the count of elements in the window
	 * @return The number of elements in the window
	 */
	UFUNCTION(BlueprintNativeEvent, BlueprintPure, Category = Window)
	int GetElementCount() const;
	virtual int GetElementCount_Implementation();

	/**
	 * Gets the number of columns
	 * @return The number of columns in the window
	 */
	UFUNCTION(BlueprintNativeEvent, BlueprintPure, Category = Window)
	int GetColumnCount() const;
	virtual int GetColumnCount_Implementation();

	/**
	 * Gets the number of rows
	 * @return The number of rows in the window
	 */
	UFUNCTION(BlueprintPure, Category = Window)
	int GetRowCount() const;

	/**
	* Can the cursor loop around the edges of the window?
	* @return if the cursor is able to loop
	*/
	UFUNCTION(BlueprintNativeEvent, BlueprintPure, Category = Window)
	bool CursorLoop();
	bool CursorLoop_Implementation();

protected:
    bool ValidInput(FKey Key, FName Action) const override;

	FReply NativeOnKeyDown(const FGeometry& MyGeometry, const FKeyEvent& InKeyEvent) override;

	/**
	* Parses cursor movement
	* @param Key The key that is being pressed
	* @param bHandled Was the event handled?
	*/
	UFUNCTION()
	void ProcessCursorInput(const FKey& Key, bool& bHandled);

	/**
	 * Process scroll input for the help window
	 * @param Key The that is being pressed
	 * @param bHandled Was the event handled?
	 */
	UFUNCTION()
	void ProcessScrollInput(const FKey& Key, bool& bHandled);

};
