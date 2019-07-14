// Created by Francesco Corso. Labeled for reuse with attribution under Creative Commons.


#include "Window.h"
#include "Runtime/UMG/Public/Components/CanvasPanel.h"
#include "Runtime/UMG/Public/Components/CanvasPanelSlot.h"

TSharedRef<SWidget> UWindow::RebuildWidget() {
	// Get the original widget
	TSharedRef<SWidget> OriginalWidget = Super::RebuildWidget();

	// Retrieve the Root Component of the widget
	UCanvasPanel* RootWidget = Cast<UCanvasPanel>(GetRootWidget());

	if (RootWidget != nullptr) {
		
		FMargin ContentsMargin(0.f);
		if (WindowBack != nullptr) {
			UCanvasPanelSlot* Slot = Cast<UCanvasPanelSlot>(WindowBack->Slot);
			if (Slot != nullptr) {
				Slot->SetAnchors(FAnchors(0.f, 0.f, 1.f, 1.f));
				Slot->SetPosition(FVector2D(0.f, 0.f));
				Slot->SetSize(FVector2D(0.f, 0.f));
			}

			ContentsMargin = WindowBack->GetFramePadding();
		}

		if (ContentsPane != nullptr) {
			UCanvasPanelSlot* Slot = Cast<UCanvasPanelSlot>(ContentsPane->Slot);
			if (Slot != nullptr) {
				Slot->SetAnchors(FAnchors(0.f, 0.f, 1.f, 1.f));
				Slot->SetPosition(ContentsMargin.GetTopLeft());
				Slot->SetSize(FVector2D(ContentsMargin.Right, ContentsMargin.Bottom));
			}
		}

	}

	return OriginalWidget;
}
