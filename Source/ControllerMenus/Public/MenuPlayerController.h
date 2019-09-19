// Created by Francesco Corso. Labeled for reuse with attribution under Creative Commons.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "Runtime/Engine/Classes/GameFramework/PlayerInput.h"
#include "Menu.h"
#include "MenuPlayerController.generated.h"

/**
 * Player controller exteneded to allow for menus to be opened and input to be passed to them.
 */
UCLASS()
class CONTROLLERMENUS_API AMenuPlayerController : public APlayerController {
	GENERATED_BODY()

	/**
	 * A stack of menus displayed on screen
	 */
	UPROPERTY()
	TArray<UMenu*> MenuStack;

public:
	/**
	* Opens a menu and adds it the stack
	* @param MenuClass - The class of the menu to add to the stack
	*/
	UFUNCTION(BlueprintCallable, Category = Menus)
	void AddMenu(TSubclassOf<UMenu> MenuClass);

	/**
	* Removes the top menu from the stack
	*/
	UFUNCTION(BlueprintCallable, Category = Menus)
	void PopMenu();

	/**
	* Clears the menu stack
	*/
	UFUNCTION(BlueprintCallable, Category = Menus)
	void ClearMenuStack();

	/**
	* Gets the menu at the top of the stack
	* @return The menu that is closest to the player
	*/
	UFUNCTION(BlueprintPure, Category = Menus)
	UMenu* GetTopMenu() const;

	/**
	* Get the keys that correspond to a specific action binding
	*/
	UFUNCTION(BlueprintPure, Category = Menu)
	void GetActionKeyBinding(FName Action, TArray<FInputActionKeyMapping>& Bindings) const;
	
};
