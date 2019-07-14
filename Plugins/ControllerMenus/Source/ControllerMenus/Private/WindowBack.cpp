// Created by Francesco Corso. Labeled for reuse with attribution under Creative Commons.


#include "WindowBack.h"

UWindowBack::UWindowBack(const FObjectInitializer& ObjectInitializer) : UUserWidget(ObjectInitializer) {
	FramePadding.Top = 12.f;
	FramePadding.Bottom = 12.f;
	FramePadding.Left = 12.f;
	FramePadding.Right = 12.f;
}

const FMargin& UWindowBack::GetFramePadding() const {
	return FramePadding;
}
