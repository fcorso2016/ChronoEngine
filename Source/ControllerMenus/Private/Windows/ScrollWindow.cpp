// Created by Francesco Corso. Labeled for reuse with attribution under Creative Commons.


#include "ScrollWindow.h"
#include "MenuPlayerController.h"
#include "Runtime/UMG/Public/Components/CanvasPanelSlot.h"

TSharedRef<SWidget> UScrollWindow::RebuildWidget() {
    // Get the original widget
    TSharedRef<SWidget> OriginalWidget = Super::RebuildWidget();

    if (ContentsPane != nullptr && ScrollableSection != nullptr) {
        UCanvasPanelSlot* Slot = Cast<UCanvasPanelSlot>(ScrollableSection->Slot);
        if (Slot != nullptr) {
            Slot->SetAnchors(FAnchors(0.f, 0.f, 1.f, 1.f));
            Slot->SetPosition(FVector2D(FMath::Max(0.f, Slot->GetPosition().X), FMath::Max(0.f, Slot->GetPosition().Y)));
            Slot->SetSize(FVector2D(FMath::Max(0.f, Slot->GetSize().X), FMath::Max(0.f, Slot->GetSize().Y)));
            Slot->SetZOrder(0);
        }

		ScrollableSection->AllowOverscroll = false;
    }

    return OriginalWidget;
}

void UScrollWindow::ScrollWindow(float Scroll) {
    static const float SCROLL_SPEED = 30.f;
	if (ScrollableSection != nullptr) {
		ScrollableSection->SetScrollOffset(ScrollableSection->GetScrollOffset() + Scroll * SCROLL_SPEED);
	}
}