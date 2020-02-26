// Created by Francesco Corso. Labeled for reuse with attribution under Creative Commons.


#include "WrittingFlipbook.h"

void UWrittingFlipbook::SetKeyFrames(TArray<FPaperFlipbookKeyFrame> Frames) {
	FramesPerSecond = 7.5f;
	KeyFrames = Frames;
}