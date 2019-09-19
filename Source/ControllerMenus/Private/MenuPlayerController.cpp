// Created by Francesco Corso. Labeled for reuse with attribution under Creative Commons.


#include "MenuPlayerController.h"

void AMenuPlayerController::AddMenu(TSubclassOf<UMenu> MenuClass) {
	UMenu* NewMenu = CreateWidget<UMenu>(this, MenuClass);
	NewMenu->AddToViewport(9999); // Z-order, this just makes it render on the very top.
	MenuStack.Add(NewMenu);
	Pause();
	SetInputMode(FInputModeUIOnly());
}

void AMenuPlayerController::PopMenu() {
	UMenu* MenuToRemove = GetTopMenu();
	MenuToRemove->RemoveFromViewport();
	MenuStack.Pop();
	if (MenuStack.Num() == 0) {
		SetInputMode(FInputModeGameOnly());
		SetPause(false);
	}
}

void AMenuPlayerController::ClearMenuStack() {
	for (UMenu* MenuToRemove : MenuStack) {
		MenuToRemove->RemoveFromViewport();
	}
	MenuStack.Empty();
}

UMenu* AMenuPlayerController::GetTopMenu() const {
	return MenuStack[MenuStack.Num() - 1];
}

void AMenuPlayerController::GetActionKeyBinding(FName Action, TArray<FInputActionKeyMapping>& Bindings) const {
	Bindings = PlayerInput->GetKeysForAction(Action);
}
