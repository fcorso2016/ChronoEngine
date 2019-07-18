// Created by Francesco Corso. Labeled for reuse with attribution under Creative Commons.


#include "CursoredWindow.h"
#include "Runtime/UMG/Public/Components/CanvasPanel.h"
#include "Runtime/UMG/Public/Components/CanvasPanelSlot.h"
#include "Runtime/UMG/Public/Components/UniformGridSlot.h"
#include "MenuPlayerController.h"

#include "Runtime/Engine/Classes/Engine/Engine.h"

UCursoredWindow::UCursoredWindow(const FObjectInitializer& ObjectInitializer) {	
	WindowInputMappings.UpInput      = "MenuUp";
	WindowInputMappings.DownInput    = "MenuDown";
	WindowInputMappings.LeftInput    = "MenuLeft";
	WindowInputMappings.RightInput   = "MenuRight";
	WindowInputMappings.ConfirmInput = "MenuConfirm";
	WindowInputMappings.CancelInput  = "MenuCancel";

	HorizontalAlignment = EHorizontalAlignment::HAlign_Left;
	VerticalAlignment   = EVerticalAlignment::VAlign_Top;

	Index = 0;
	bIsActive = true;
	bIsFocusable = true;
}

TSharedRef<SWidget> UCursoredWindow::RebuildWidget() {
	// Get the original widget
	TSharedRef<SWidget> OriginalWidget = Super::RebuildWidget();

	// Retrieve the Root Component of the widget
	UCanvasPanel* RootWidget = Cast<UCanvasPanel>(GetRootWidget());

	if (RootWidget != nullptr && ContentsPane != nullptr && SelectionArea != nullptr) {
		UCanvasPanelSlot* Slot = Cast<UCanvasPanelSlot>(SelectionArea->Slot);
		if (Slot != nullptr) {
			Slot->SetAnchors(FAnchors(0.f, 0.f, 1.f, 1.f));
			Slot->SetPosition(FVector2D(FMath::Max(0.f, Slot->GetPosition().X), FMath::Max(0.f, Slot->GetPosition().Y)));
			Slot->SetSize(FVector2D(FMath::Max(0.f, Slot->GetSize().X), FMath::Max(0.f, Slot->GetSize().Y)));
			Slot->SetZOrder(0);
		}

		for (int i = 0; i < GetElementCount(); i++) {
			AddElement(i);
		}
		SetCursorPosition();
	}

	return OriginalWidget;
}

void UCursoredWindow::NativeConstruct() {
	Super::NativeConstruct();
	if (GetActive()) {
		SetKeyboardFocus();
	}
}

int UCursoredWindow::GetIndex() const {
	return Index;
}

void UCursoredWindow::Select(int NewIndex) {
	Index = FMath::Clamp(NewIndex, 0, GetElementCount() - 1);
	SetCursorPosition();
}

void UCursoredWindow::Select(USelectableOption* Option) {
	int NewIndex = Elements.IndexOfByKey(Option);
	Select(NewIndex);
}

void UCursoredWindow::Deselect() {
	Index = -1;
	SetCursorPosition();
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

void UCursoredWindow::SetCursorPosition() {
	if (Index >= 0 && Index < GetElementCount() && WindowCursor != nullptr) {
		UUniformGridSlot* Slot = Cast<UUniformGridSlot>(WindowCursor->Slot);
		if (Slot != nullptr) {
			Slot->SetRow(Index / GetColumnCount());
			Slot->SetColumn(Index % GetColumnCount());
			Slot->SetHorizontalAlignment(EHorizontalAlignment::HAlign_Fill);
			Slot->SetVerticalAlignment(EVerticalAlignment::VAlign_Fill);
		}

		WindowCursor->SetVisibility(ESlateVisibility::Visible);
	} else if (WindowCursor != nullptr) {
		WindowCursor->SetVisibility(ESlateVisibility::Collapsed);
	}
}

void UCursoredWindow::AddElement(int NewIndex) {
	if (NewIndex >= 0 && NewIndex < GetElementCount()) {
		USelectableOption* Element = CreateNewElement(NewIndex);
		Elements.Add(Element);
		Element->Owner = this;

		if (SelectionArea != nullptr) {
			SelectionArea->AddChildToUniformGrid(Element);
			UUniformGridSlot* Slot = Cast<UUniformGridSlot>(Element->Slot);
			if (Slot != nullptr) {
				Slot->SetRow(NewIndex / GetColumnCount());
				Slot->SetColumn(NewIndex % GetColumnCount());
				Slot->SetHorizontalAlignment(HorizontalAlignment);
				Slot->SetVerticalAlignment(VerticalAlignment);
			}
		}
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

bool UCursoredWindow::CursorLoop_Implementation() {
	return false;
}

bool UCursoredWindow::ValidInput(FKey Key, FName Action) const {
	if (GetActive() && GetOwningPlayer() != nullptr) {
		AMenuPlayerController* Controller = Cast<AMenuPlayerController>(GetOwningPlayer());
		if (Controller != nullptr) {
			TArray<FInputActionKeyMapping> ActionBindings;
			Controller->GetActionKeyBinding(Action, ActionBindings);
			for (FInputActionKeyMapping Mapping : ActionBindings) {
				if (Mapping.Key == Key) {
					return true;
				}
			}
		}
	}

	return false;
}

FReply UCursoredWindow::NativeOnKeyDown(const FGeometry& MyGeometry, const FKeyEvent& InKeyEvent) {
	FReply OldHandling = Super::NativeOnKeyDown(MyGeometry, InKeyEvent);

	bool bHandled = false;
	FKey Key = InKeyEvent.GetKey();
	ProcessCursorInput(Key, bHandled);
	if (ValidInput(Key, WindowInputMappings.ConfirmInput)) {
		OnConfirm.Broadcast(Elements[Index]->Symbol);
	} else if (ValidInput(Key, WindowInputMappings.CancelInput)) {
		OnCancel.Broadcast();
	}

	if (bHandled) {
		return FReply::Handled();
	}
	return OldHandling;
}

void UCursoredWindow::ProcessCursorInput(const FKey& Key, bool& bHandled) {
	if (GetElementCount() > 0) {
		if (ValidInput(Key, WindowInputMappings.UpInput)) {
			if (Index >= GetColumnCount()) {
				Select(Index - GetColumnCount());
				bHandled = true;
			} else if (CursorLoop()) {
				Select(GetElementCount() + (Index - GetColumnCount()));
				bHandled = true;
			}
		}

		if (ValidInput(Key, WindowInputMappings.DownInput)) {
			if (Index < GetElementCount() - GetColumnCount()) {
				Select(Index + GetColumnCount());
				bHandled = true;
			} else if (CursorLoop()) {
				Select(Index + GetColumnCount() - GetElementCount());
				bHandled = true;
			}
		}

		if (GetColumnCount() > 1) {
			if (ValidInput(Key, WindowInputMappings.LeftInput)) {
				if (Index > 0) {
					Select(Index - 1);
					bHandled = true;
				} else if (CursorLoop()) {
					Select(GetElementCount() - 1);
					bHandled = true;
				}
			}

			if (ValidInput(Key, WindowInputMappings.RightInput)) {
				if (Index < GetElementCount() - 1) {
					Select(Index + 1);
					bHandled = true;
				} else if (CursorLoop()) {
					Select(0);
					bHandled = true;
				}
			}
		}
	}
}
