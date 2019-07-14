// Fill out your copyright notice in the Description page of Project Settings.


#include "Window.h"

TSharedRef<SWidget> UWindow::RebuildWidget() {
	if (WindowBack != nullptr) {
		Padding = WindowBack->Padding;
	}

	return Super::RebuildWidget();
}
