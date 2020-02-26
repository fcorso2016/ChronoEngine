// Created by Francesco Corso. Labeled for reuse with attribution under Creative Commons.


#include "DynamicSprite.h"

void UDynamicSprite::SetAppearance(UTexture* Texture, FVector2D StartLocation, FVector2D Size) {
	SourceTexture = Texture;
	SourceUV = StartLocation;
	SourceDimension = Size;
	PixelsPerUnrealUnit = 1.f;
	PivotMode = ESpritePivotMode::Bottom_Center;
	CreatePolygonFromBoundingBox(CollisionGeometry, true);
	CreatePolygonFromBoundingBox(RenderGeometry, true);
	RebuildRenderData();
}
