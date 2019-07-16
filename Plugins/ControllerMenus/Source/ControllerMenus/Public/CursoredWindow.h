// Created by Francesco Corso. Labeled for reuse with attribution under Creative Commons.

#pragma once

#include "CoreMinimal.h"
#include "Window.h"
#include "Cursor.h"
#include "CursoredWindow.generated.h"

/**
* Struct that stores the input handlers for the window
*/
USTRUCT(BlueprintType)
struct FInputActions {
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
};

/**
 * Delegate for when the user presses confirm 
 */
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FProcessConfirm, FName, SelectionSymbol);

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
	 * List of all input mappings 
	 */
	UPROPERTY(BlueprintReadOnly, Category = Components, meta = (BindWidget))
	UCursor* WindowCursor;

private:
	/** 
	 * List of all input mappings
	 */
	UPROPERTY(EditAnywhere, Category = Input)
	FInputActions WindowInputMappings;

	/**
	 * The index of the cursor in the window
	 */
	UPROPERTY()
	int Index;

	/**
	 * Get the window's activation status 
	 */
	UPROPERTY()
	bool bIsActive;

public:
	

	/**
	 * The delegate called when the player presses confirm/clicks on an option
	 */
	UPROPERTY(BlueprintAssignable, Category = Input)
	FProcessConfirm OnConfirm;
	
	UCursoredWindow(const FObjectInitializer& ObjectInitializer);

	/**
	 * Get the index of the cursor
	 * @return The index of the cursor in the window
	 */
	UFUNCTION(BlueprintPure, Category = Input)
	int GetIndex() const;

	/**
	 * Set the index of the cursor
	 * @param NewIndex The new index of the cursor
	 */
	UFUNCTION(BlueprintCallable, Category = Input)
	void SetIndex(int NewIndex);

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

};
