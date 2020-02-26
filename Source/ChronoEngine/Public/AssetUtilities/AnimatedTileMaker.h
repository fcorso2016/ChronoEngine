// Created by Francesco Corso. Labeled for reuse with attribution under Creative Commons.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "AnimatedTileMaker.generated.h"

/**
 * Blueprint function library who's sole purpose is to make the flipbookification of animated tilesets easier
 */
UCLASS()
class CHRONOENGINE_API UAnimatedTileMaker : public UBlueprintFunctionLibrary {
	GENERATED_BODY()

public:
	/**
	* Create new tilesets from a base
	* @param TotalTiles - the number of tiles being generated
	* @param FrameDirectory - the folder from which all the frames come from
	* @param FrameDestination - the folder where everything is eventually going to be saved
	* @param FrameName - the name of each frame's asset
	* @param StartIndex1 - the starting index of the first frame
	* @param StartIndex2 - the starting index of the second frame
	* @param StartIndex3 - the starting index of the third frame
	*/
	UFUNCTION(BlueprintCallable, Category = "Debug|Tilesets")
	static void CreateAutotileFlipbooks(const int TotalTiles, const FString FrameDirectory, const FString FrameDestination, const FString FrameName, const int StartIndex1 = 0, const int StartIndex2 = 4, const int StartIndex3 = 8);

	/**
	* Helper function for Create Tile Flipbooks
	* @param i - the value of the variable i in the outer loop
	* @param j - the value of the variable j in the inner loop
	* @param FrameDirectory - the folder from which all the frames come from
	* @param FrameDestination - the folder where everything is eventually going to be saved
	* @param FrameName - the name of each frame's asset
	* @param StartIndex1 - the starting index of the first frame
	* @param StartIndex2 - the starting index of the second frame
	* @param StartIndex3 - the starting index of the third frame
	*/
	static void CreateFlipbook(int& i, int& j, const FString& FrameDirectory, const FString& FrameDestination, const FString& FrameName, const int& StartIndex1, const int& StartIndex2, const int& StartIndex3);

	/**
	* Creates larger autotile edges from base info
	* @param TotalTiles - the number of tiles being generated
	* @param FrameDirectory - the folder from which all the frames come from
	* @param FrameDestination - the folder where everything is eventually going to be saved
	* @param FrameName - the name of each frame's asset
	*
	*/
	UFUNCTION(BlueprintCallable, Category = "Debug|Tilesets")
	static void CreateLargeAutotiles(const int TotalTiles, const FString FrameDirectory, const FString FrameDestination, const FString FrameName);

	/**
	* Creates a full character set of sprites for the game
	* @param FrameDirectory - the folder from which all the frames come from
	* @param CharacterName - the name of character
	* @param CharacterIndex - the index of the character in question
	* @param AnimationIndex - the index of the character's animation
	*/
	UFUNCTION(BlueprintCallable, Category = "Debug|Chracter Sets")
	static void CreateFullCharacter(const FString FrameDirectory, const FString& CharacterName, const bool IsPlayable, const int CharacterIndex, const int AnimationIndex);

	/**
	 * Take a texture an turn it into a spriteset
	 * @param TextureDirectory - the folder where the texture is stored
	 * @param TextureName - the name of the texture in question
	 * @param bSingleCharacter - if the texture is a single character or not
	 * @param bIsEmote - if the character is emoting or walking
	 */
	UFUNCTION(BlueprintCallable, Category = "Debug|Character Sets")
	static void ExtractCharacterSprites(const FString TextureDirectory, const FString TextureName, bool bSingleCharacter = false, bool bIsEmote = false);

	/**
	* Create the base character flipbooks
	* @param FrameDirectory - the folder from which all the frames come from
	* @param SourceTexture - the name of the source texture\
	* @param CharacterIndex - the index of the character in question
	*/
	UFUNCTION(BlueprintCallable, Category = "Debug|Chracter Sets")
	static void CreateBaseCharacter(const FString& FrameDirectory, const FString& SourceTexture, const int CharacterIndex);

	/**
	* Create idle character set
	* @param FrameDirectory - the folder from which all the frames come from
	* @param SourceTexture - the name of the source texture
	* @param CharacterIndex - the index of the character in question
	*/
	static void CreateIdleCharacter(const FString& FrameDirectory, const FString& SourceTexture, const int& CharacterIndex);

	/**
	* Create walking character set
	* @param FrameDirectory - the folder from which all the frames come from
	* @param SourceTexture - the name of the source texture
	* @param CharacterIndex - the index of the character in question
	*/
	static void CreateWalkingCharacter(const FString& FrameDirectory, const FString& SourceTexture, const int& CharacterIndex);

	/**
	* Create the emote set for a chracter
	* @param FrameDirectory - the folder from which all the frames come from
	* @param SourceTexture - the name of the source texture
	* @param CharacterIndex - the index of the character in question
	*/
	static void CreateEmoteSet(const FString& FrameDirectory, const FString& SourceTexture, const int& CharacterIndex);

	/**
	* Create the animation set
	* @param FrameDirectory - the folder from which all the frames come from
	* @param CharacterName - the name of character
	* @param AnimationIndex - the index of the character's animation
	*/
	static void CreateAnimation(const FString& FrameDirectory, const FString& CharacterName, const int& AnimationIndex);


	/**
	* Create the battle sprite of a character
	* @param FrameDirectory - the folder from which all the frames come from
	* @param CharacterName - the name of character
	*/
	UFUNCTION(BlueprintCallable, Category = "Debug|Character Sets")
	static void CreateBattleSprites(const FString FrameDirectory, const FString CharacterName);
	
};
