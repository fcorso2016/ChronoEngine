// Created by Francesco Corso. Labeled for reuse with attribution under Creative Commons.


#include "ChronoCodeUtilities.h"
#include "GameFramework/PlayerController.h"
#include "Engine/World.h"
#include "Engine/GameViewportClient.h"

FText UChronoCodeUtilities::GetSuffixFromIndex(int Index) {
	FString Suffix;
	
	if (Index >= 0) {
		const char StartingCharacter = 'A';
		do {
			Suffix.AppendChar(StartingCharacter + Index % 26);
			Index /= 26;
		} while (Index > 0);
	}

	return FText::FromString(Suffix);
}

EControlMode UChronoCodeUtilities::GetCurrentViewMode(const APlayerController* PlayerController) {
	if (IsValid(PlayerController)) {
		UGameViewportClient* GameViewportClient = PlayerController->GetWorld()->GetGameViewport();
		ULocalPlayer* LocalPlayer = PlayerController->GetLocalPlayer();

		bool ignore = GameViewportClient->IgnoreInput();
		EMouseCaptureMode capt = GameViewportClient->CaptureMouseOnClick();

		if (ignore == false && capt == EMouseCaptureMode::CaptureDuringMouseDown) {
			return EControlMode::GameAndUI;  // Game And UI
		} else if (ignore == true && capt == EMouseCaptureMode::NoCapture) {
			return EControlMode::UIOnly;  // UI Only
		} else {
			return EControlMode::GameOnly;  // Game Only
		}
	}

	return EControlMode::None;
}

int UChronoCodeUtilities::GetNullIndex() {
	return INDEX_NONE;
}

FVector2D UChronoCodeUtilities::GetSpriteSize(UPaperSprite* Sprite) {
	return Sprite->GetSourceSize();
}