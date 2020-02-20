// Created by Francesco Corso. Labeled for reuse with attribution under Creative Commons.


#include "SelectableOption.h"
#include "Runtime/UMG/Public/Components/CanvasPanel.h"
#include "Runtime/UMG/Public/Components/CanvasPanelSlot.h"
#include "Windows/CursoredWindow.h"

TSharedRef<SWidget> USelectableOption::RebuildWidget() {
	// Get the original widget
	TSharedRef<SWidget> OriginalWidget = Super::RebuildWidget();

	if (Interactable != nullptr) {
		UCanvasPanelSlot* Slot = Cast<UCanvasPanelSlot>(Interactable->Slot);
		if (Slot != nullptr) {
			Slot->SetAnchors(FAnchors(0.f, 0.f, 1.f, 1.f));
			Slot->SetPosition(FVector2D(0.f, 0.f));
			Slot->SetSize(FVector2D(0.f, 0.f));
			Slot->SetZOrder(-100);
		}

		Interactable->OnHovered.RemoveAll(this);
		Interactable->OnClicked.RemoveAll(this);

		Interactable->OnHovered.AddDynamic(this, &USelectableOption::SelectElement);
		Interactable->OnClicked.AddDynamic(this, &USelectableOption::ClickElement);
	}

	return OriginalWidget;
}

void USelectableOption::SelectElement() {
	if (Owner->GetActive()) {
		Owner->Select(this);
	}
}

void USelectableOption::ClickElement() {
	if (Owner->GetActive()) {
		Owner->Select(this);
		if (Owner->CanConfirm()) {
			Owner->OnConfirm.Broadcast(Owner->GetIndex(), Symbol);
		}
	}
}

bool  USelectableOption::CanSelect_Implementation() {
	return true;
}
