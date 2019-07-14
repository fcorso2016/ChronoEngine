// Created by Francesco Corso. Labeled for reuse with attribution under Creative Commons.


#include "Window.h"

TSharedRef<SWidget> UWindow::RebuildWidget() {
	if (WindowBack != nullptr) {
		Padding = WindowBack->Padding;
	}

	return Super::RebuildWidget();
}
