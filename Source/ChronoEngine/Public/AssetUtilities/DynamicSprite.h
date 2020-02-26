// Created by Francesco Corso. Labeled for reuse with attribution under Creative Commons.

#pragma once

#include "CoreMinimal.h"
#include "PaperSprite.h"
#include "DynamicSprite.generated.h"

/**
 * Sprite that allows the user to set a texture, size and start location
 */
UCLASS(NotBlueprintable)
class CHRONOENGINE_API UDynamicSprite : public UPaperSprite {
	GENERATED_BODY()

public:
	/**
	 * Set the appearance of the character
	 * @param Texture the texture that determines appearance
	 * @param StartLocation the offset of the sprite's appearance
	 * @param Size the size of the sprite
	 */
	void SetAppearance(UTexture* Texture, FVector2D StartLocation, FVector2D Size);
	
};
