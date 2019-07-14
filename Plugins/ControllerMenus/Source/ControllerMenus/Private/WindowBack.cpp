// Fill out your copyright notice in the Description page of Project Settings.


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
