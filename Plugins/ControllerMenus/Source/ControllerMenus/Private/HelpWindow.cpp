// Created by Francesco Corso. Labeled for reuse with attribution under Creative Commons.


#include "HelpWindow.h"
#include "MenuPlayerController.h"
#include "Runtime/UMG/Public/Components/CanvasPanelSlot.h"

UHelpWindow::UHelpWindow(const FObjectInitializer& ObjectInitializer) : UWindow(ObjectInitializer) {
    WindowInputMappings.ScrollUp   = "MenuScrollUp";
    WindowInputMappings.ScrollDown = "MenuScrollDown";

    bIsFocusable = true;
}

TSharedRef<SWidget> UHelpWindow::RebuildWidget() {
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
    }

    return OriginalWidget;
}

FReply UHelpWindow::NativeOnKeyDown(const FGeometry &MyGeometry, const FKeyEvent &InKeyEvent) {
    static const float SCROLL_SPEED = 30.f;
    FReply OldHandling = UUserWidget::NativeOnKeyDown(MyGeometry, InKeyEvent);

    bool bHandled = false;
    if (ScrollableSection != nullptr) {
        FKey Key = InKeyEvent.GetKey();
        if (ValidInput(Key, WindowInputMappings.ScrollUp)) {
            ScrollableSection->SetScrollOffset(ScrollableSection->GetScrollOffset() - SCROLL_SPEED);
            bHandled = true;
        } else if (ValidInput(Key, WindowInputMappings.ScrollDown)) {
            ScrollableSection->SetScrollOffset(ScrollableSection->GetScrollOffset() + SCROLL_SPEED);
            bHandled = true;
        }
    }

    if (bHandled) {
        return FReply::Handled();
    }
    return OldHandling;
}
