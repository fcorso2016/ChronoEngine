// Created by Francesco Corso. Labeled for reuse with attribution under Creative Commons.


#include "CursoredWindow.h"

UCursoredWindow::UCursoredWindow(const FObjectInitializer& ObjectInitializer) {
	Index = 0;

	// Set the default input mappings
	WindowInputMappings.UpInput      = "MenuUp";
	WindowInputMappings.DownInput    = "MenuDown";
	WindowInputMappings.LeftInput    = "MenuLeft";
	WindowInputMappings.RightInput   = "MenuRight";
	WindowInputMappings.ConfirmInput = "MenuConfirm";
	WindowInputMappings.CancelInput  = "MenuCancel";
}

int UCursoredWindow::GetIndex() const {
	return Index;
}

void UCursoredWindow::SetIndex(int NewIndex) {
	Index = FMath::Clamp(NewIndex, 0, GetElementCount() - 1);
}

bool UCursoredWindow::GetActive() const {
	return bIsActive;
}

void UCursoredWindow::SetActive(bool bActive) {
	bIsActive = bActive;
	if (bIsActive) {
		SetKeyboardFocus();
	}
}

int UCursoredWindow::GetElementCount_Implementation() {
	return 0;
}

int UCursoredWindow::GetColumnCount_Implementation() {
	return 1;
}

int UCursoredWindow::GetRowCount() const {
	return FMath::Max(1, (GetElementCount() + GetColumnCount() - 1) / GetColumnCount());
}
