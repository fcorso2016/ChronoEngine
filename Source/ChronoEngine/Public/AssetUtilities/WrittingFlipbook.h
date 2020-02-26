// Created by Francesco Corso. Labeled for reuse with attribution under Creative Commons.

#pragma once

#include "CoreMinimal.h"
#include "PaperFlipbook.h"
#include "WrittingFlipbook.generated.h"

/**
 * Special flipbook class created soley for the purpose of editing a flipbook's information
 */
UCLASS(NotBlueprintable)
class CHRONOENGINE_API UWrittingFlipbook : public UPaperFlipbook {
	GENERATED_BODY()

public:
	/**
	* Copy key frames from another source
	* @param Frames - the frames being copied over
	*/
	void SetKeyFrames(TArray<FPaperFlipbookKeyFrame> Frames);
	
};
