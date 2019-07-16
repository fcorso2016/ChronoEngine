// Created by Francesco Corso. Labeled for reuse with attribution under Creative Commons.


#include "SelectableOption.h"
#include "Runtime/UMG/Public/Components/CanvasPanel.h"
#include "Runtime/UMG/Public/Components/CanvasPanelSlot.h"

TSharedRef<SWidget> USelectableOption::RebuildWidget() {
	// Get the original widget
	TSharedRef<SWidget> OriginalWidget = Super::RebuildWidget();

	// Retrieve the Root Component of the widget
	UCanvasPanel* RootWidget = Cast<UCanvasPanel>(GetRootWidget());

	if (RootWidget != nullptr && Interactable != nullptr) {
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

}

void USelectableOption::ClickElement() {

}
