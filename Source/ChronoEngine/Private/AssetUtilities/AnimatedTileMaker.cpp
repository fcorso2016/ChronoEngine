// Created by Francesco Corso. Labeled for reuse with attribution under Creative Commons.


#include "AnimatedTileMaker.h"
#include "WrittingFlipbook.h"
#include "PaperSprite.h"
#include "Runtime/CoreUObject/Public/UObject/Package.h"
#include "Runtime/CoreUObject/Public/Misc/PackageName.h"
#include "Runtime/Engine/Classes/Engine/Engine.h"
#include "DynamicSprite.h"

void UAnimatedTileMaker::CreateAutotileFlipbooks(const int TotalTiles, const FString FrameDirectory, const FString FrameDestination, const FString FrameName, const int StartIndex1, const int StartIndex2, const int StartIndex3) {
	for (int i = 0; i < TotalTiles / 4; i++) {
		for (int j = 0; j < 4; j++) {
			CreateFlipbook(i, j, FrameDirectory, FrameDestination, FrameName, StartIndex1, StartIndex2, StartIndex3);
		}
	}
}

void UAnimatedTileMaker::CreateFlipbook(int& i, int& j, const FString& FrameDirectory, const FString& FrameDestination, const FString& FrameName, const int& StartIndex1, const int& StartIndex2, const int& StartIndex3) {
	// Initialize the name of the new flipbook
	FString TileName = FrameName + TEXT("_") + FString::FromInt(i * 4 + j);

	// Initialize Directory
	FString PackageName = TEXT("/Game/") + FrameDestination;
	PackageName += TileName;
	UPackage* Package = CreatePackage(NULL, *PackageName);
	Package->FullyLoad();

	// Edit the contents of the flipbook
	UPaperFlipbook* NewFlipbook = NewObject<UWrittingFlipbook>(Package, *TileName, RF_Public | RF_Standalone | RF_MarkAsRootSet);
	NewFlipbook->AddToRoot();
	TArray<FString> FrameNames;
	FrameNames.Add(FrameName + TEXT("_") + FString::FromInt(StartIndex2 + i * 12 + j));
	FrameNames.Add(FrameName + TEXT("_") + FString::FromInt(StartIndex1 + i * 12 + j));
	FrameNames.Add(FrameName + TEXT("_") + FString::FromInt(StartIndex2 + i * 12 + j));
	FrameNames.Add(FrameName + TEXT("_") + FString::FromInt(StartIndex3 + i * 12 + j));
	TArray<FPaperFlipbookKeyFrame> KeyFrames;
	for (FString Name : FrameNames) {
		FString FileName = TEXT("/Game/") + FrameDirectory + Name + TEXT(".") + Name;
		FPaperFlipbookKeyFrame KeyFrame;
		KeyFrame.FrameRun = 1;
		KeyFrame.Sprite = LoadObject<UPaperSprite>(NULL, *FileName);
		if (KeyFrame.Sprite == nullptr) {
			if (GEngine)
				GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FileName);
		} else {
			if (GEngine)
				GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FileName);
		}
		KeyFrames.Add(KeyFrame);
	}
	Cast<UWrittingFlipbook>(NewFlipbook)->SetKeyFrames(KeyFrames);

	// Save the tile
	FString PackageFileName = FPackageName::LongPackageNameToFilename(PackageName, FPackageName::GetAssetPackageExtension());
	bool bSaved = UPackage::SavePackage(Package, NewFlipbook, EObjectFlags::RF_Public | EObjectFlags::RF_Standalone, *PackageFileName, GError, nullptr);
}

void UAnimatedTileMaker::CreateLargeAutotiles(const int TotalTiles, const FString FrameDirectory, const FString FrameDestination, const FString FrameName) {
	// Get the extentions for all the sides
	const FString Positions[] = { "Top", "Bottom", "Left", "Right" };
	const FString Sizes[] = { "01x", "02x", "04x", "08x", "16x" };

	for (int i = 0; i < TotalTiles; i++) {
		for (FString Position : Positions) {
			for (FString Size : Sizes) {
				// Initialize the name of the new flipbook
				FString TileName = FrameName + Position + Size + TEXT("_") + FString::FromInt(i);

				// Initialize Directory
				FString PackageName = TEXT("/Game/") + FrameDestination;
				PackageName += TileName;
				UPackage* Package = CreatePackage(NULL, *PackageName);
				Package->FullyLoad();

				// Edit the contents of the flipbook
				UPaperFlipbook* NewFlipbook = NewObject<UWrittingFlipbook>(Package, *TileName, RF_Public | RF_Standalone | RF_MarkAsRootSet);
				NewFlipbook->AddToRoot();
				TArray<FString> FrameNames;
				FrameNames.Add(FrameName + Position + Size + TEXT("__") + FString::FromInt(i * 3 + 1));
				FrameNames.Add(FrameName + Position + Size + TEXT("__") + FString::FromInt(i * 3 + 0));
				FrameNames.Add(FrameName + Position + Size + TEXT("__") + FString::FromInt(i * 3 + 1));
				FrameNames.Add(FrameName + Position + Size + TEXT("__") + FString::FromInt(i * 3 + 2));
				TArray<FPaperFlipbookKeyFrame> KeyFrames;
				for (FString Name : FrameNames) {
					FString FileName = TEXT("/Game/") + FrameDirectory + Name + TEXT(".") + Name;
					FPaperFlipbookKeyFrame KeyFrame;
					KeyFrame.FrameRun = 1;
					KeyFrame.Sprite = LoadObject<UPaperSprite>(NULL, *FileName);
					if (KeyFrame.Sprite == nullptr) {
						if (GEngine)
							GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FileName);
					} else {
						if (GEngine)
							GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FileName);
					}
					KeyFrames.Add(KeyFrame);
				}
				Cast<UWrittingFlipbook>(NewFlipbook)->SetKeyFrames(KeyFrames);

				// Save the tile
				FString PackageFileName = FPackageName::LongPackageNameToFilename(PackageName, FPackageName::GetAssetPackageExtension());
				bool bSaved = UPackage::SavePackage(Package, NewFlipbook, EObjectFlags::RF_Public | EObjectFlags::RF_Standalone, *PackageFileName, GError, nullptr);
			}
		}
	}
}

void UAnimatedTileMaker::CreateFullCharacter(const FString FrameDirectory, const FString& CharacterName, const bool IsPlayable, const int CharacterIndex, const int AnimationIndex) {
	CreateBaseCharacter(FrameDirectory, TEXT("chara"), CharacterIndex);
	CreateEmoteSet(FrameDirectory, TEXT("emote"), CharacterIndex);
	CreateAnimation(FrameDirectory, CharacterName, AnimationIndex);
}

void UAnimatedTileMaker::ExtractCharacterSprites(const FString TextureDirectory, const FString TextureName, bool bSingleCharacter, bool bIsEmote) {
	// Load the source texture
	FString TextureFileName = TEXT("/Game/") + TextureDirectory + TEXT("/") + TextureName + TEXT(".") + TextureName;
	UTexture2D* Texture = LoadObject<UTexture2D>(NULL, *TextureFileName);
	int FrameWidth = Texture->GetSizeX() / (bSingleCharacter ? 3 : 12);
	int FrameHeight = Texture->GetSizeY() / (bSingleCharacter ? 4 : 8);

	// Create all the frames
	for (int i = 0; i < (bSingleCharacter ? 1 : 8); i++) {
		for (int j = 0; j < 12; j++) {
			// Initialize Directory
			FString PackageName = TEXT("/Game/") + TextureDirectory + TEXT("/") + TextureName + TEXT("/index") + FString::FromInt(i) + TEXT("/");
			FString DestinationName = TextureName + TEXT("_") + FString::FromInt(i) + TEXT("_") + FString::FromInt(j);
			PackageName += DestinationName;
			UPackage* Package = CreatePackage(NULL, *PackageName);
			Package->FullyLoad();

			FString AssetName = PackageName + TEXT(".") + DestinationName;
			if (LoadObject<UObject>(NULL, *AssetName) == nullptr) {
				// Edit the contents of the sprite
				UPaperSprite* NewSprite = NewObject<UDynamicSprite>(Package, *DestinationName, RF_Public | RF_Standalone | RF_MarkAsRootSet);
				NewSprite->AddToRoot();

				// Get the offset of the sprite
				int OffsetX = ((i % 4) * 3 * FrameWidth) + ((j % 3) * FrameWidth);
				int OffsetY = ((i / 4) * 4 * FrameHeight) + ((j / 3) * FrameHeight);
				Cast<UDynamicSprite>(NewSprite)->SetAppearance(Texture, FVector2D(OffsetX, OffsetY), FVector2D(FrameWidth, FrameHeight));

				// Save the sprite
				FString PackageFileName = FPackageName::LongPackageNameToFilename(PackageName, FPackageName::GetAssetPackageExtension());
				bool bSaved = UPackage::SavePackage(Package, NewSprite, EObjectFlags::RF_Public | EObjectFlags::RF_Standalone, *PackageFileName, GError, nullptr);
			} else {
				if (GEngine)
					GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, AssetName);
			}
		}

		if (bIsEmote) {
			CreateEmoteSet(TextureDirectory + +TEXT("/") + TextureName + TEXT("/index") + FString::FromInt(i), TextureName, i);
		} else {
			CreateBaseCharacter(TextureDirectory + +TEXT("/") + TextureName + TEXT("/index") + FString::FromInt(i), TextureName, i);
		}
	}
}

void UAnimatedTileMaker::CreateBaseCharacter(const FString& FrameDirectory, const FString& SourceTexture, const int CharacterIndex) {
	CreateIdleCharacter(FrameDirectory, SourceTexture, CharacterIndex);
	CreateWalkingCharacter(FrameDirectory, SourceTexture, CharacterIndex);
}

void UAnimatedTileMaker::CreateIdleCharacter(const FString& FrameDirectory, const FString& SourceTexture, const int& CharacterIndex) {
	static FString Directions[] = { TEXT("Down"), TEXT("Left"), TEXT("Right"), TEXT("Up") };
	for (int i = 0; i < 4; i++) {
		// Initialize the Name of the New Flipbook
		FString FlipbookName = SourceTexture + TEXT("_") + FString::FromInt(CharacterIndex);
		FString DestinationName = SourceTexture + TEXT("_") + FString::FromInt(CharacterIndex) + TEXT("_Idle") + Directions[i];
		FString DestinationDirectory = FrameDirectory + TEXT("/Idle/");

		// Initialize Directory
		FString PackageName = TEXT("/Game/") + DestinationDirectory;
		PackageName += DestinationName;
		UPackage* Package = CreatePackage(NULL, *PackageName);
		Package->FullyLoad();

		FString AssetName = PackageName + TEXT(".") + DestinationName;
		if (LoadObject<UObject>(NULL, *AssetName) == nullptr) {
			// Edit the contents of the flipbook
			UPaperFlipbook* NewFlipbook = NewObject<UWrittingFlipbook>(Package, *DestinationName, RF_Public | RF_Standalone | RF_MarkAsRootSet);
			NewFlipbook->AddToRoot();
			TArray<FString> FrameNames;
			FrameNames.Add(FlipbookName + TEXT("_") + FString::FromInt(i * 3 + 1));
			TArray<FPaperFlipbookKeyFrame> KeyFrames;
			for (FString Name : FrameNames) {
				FString FileName = TEXT("/Game/") + FrameDirectory + TEXT("/") + Name + TEXT(".") + Name;
				FPaperFlipbookKeyFrame KeyFrame;
				KeyFrame.FrameRun = 1;
				KeyFrame.Sprite = LoadObject<UPaperSprite>(NULL, *FileName);
				if (KeyFrame.Sprite == nullptr) {
					if (GEngine)
						GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FileName);
				} else {
					if (GEngine)
						GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FileName);
				}
				KeyFrames.Add(KeyFrame);
			}
			Cast<UWrittingFlipbook>(NewFlipbook)->SetKeyFrames(KeyFrames);

			// Save the flipbook
			FString PackageFileName = FPackageName::LongPackageNameToFilename(PackageName, FPackageName::GetAssetPackageExtension());
			bool bSaved = UPackage::SavePackage(Package, NewFlipbook, EObjectFlags::RF_Public | EObjectFlags::RF_Standalone, *PackageFileName, GError, nullptr);
		} else {
			if (GEngine)
				GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, AssetName);
		}
	}
}

void UAnimatedTileMaker::CreateWalkingCharacter(const FString& FrameDirectory, const FString& SourceTexture, const int& CharacterIndex) {
	static FString Directions[] = { TEXT("Down"), TEXT("Left"), TEXT("Right"), TEXT("Up") };
	for (int i = 0; i < 4; i++) {
		// Initialize the Name of the New Flipbook
		FString FlipbookName = SourceTexture + TEXT("_") + FString::FromInt(CharacterIndex);
		FString DestinationName = SourceTexture + TEXT("_") + FString::FromInt(CharacterIndex) + TEXT("_Walk") + Directions[i];
		FString DestinationDirectory = FrameDirectory + TEXT("/Walk/");

		// Initialize Directory
		FString PackageName = TEXT("/Game/") + DestinationDirectory;
		PackageName += DestinationName;
		UPackage* Package = CreatePackage(NULL, *PackageName);
		Package->FullyLoad();

		FString AssetName = PackageName + TEXT(".") + DestinationName;
		if (LoadObject<UObject>(NULL, *AssetName) == nullptr) {
			// Edit the contents of the flipbook
			UPaperFlipbook* NewFlipbook = NewObject<UWrittingFlipbook>(Package, *DestinationName, RF_Public | RF_Standalone | RF_MarkAsRootSet);
			NewFlipbook->AddToRoot();
			TArray<FString> FrameNames;
			FrameNames.Add(FlipbookName + TEXT("_") + FString::FromInt(i * 3 + 1));
			FrameNames.Add(FlipbookName + TEXT("_") + FString::FromInt(i * 3 + 0));
			FrameNames.Add(FlipbookName + TEXT("_") + FString::FromInt(i * 3 + 1));
			FrameNames.Add(FlipbookName + TEXT("_") + FString::FromInt(i * 3 + 2));
			TArray<FPaperFlipbookKeyFrame> KeyFrames;
			for (FString Name : FrameNames) {
				FString FileName = TEXT("/Game/") + FrameDirectory + TEXT("/") + Name + TEXT(".") + Name;
				FPaperFlipbookKeyFrame KeyFrame;
				KeyFrame.FrameRun = 1;
				KeyFrame.Sprite = LoadObject<UPaperSprite>(NULL, *FileName);
				if (KeyFrame.Sprite == nullptr) {
					if (GEngine)
						GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FileName);
				} else {
					if (GEngine)
						GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FileName);
				}
				KeyFrames.Add(KeyFrame);
			}
			Cast<UWrittingFlipbook>(NewFlipbook)->SetKeyFrames(KeyFrames);

			// Save the flipbook
			FString PackageFileName = FPackageName::LongPackageNameToFilename(PackageName, FPackageName::GetAssetPackageExtension());
			bool bSaved = UPackage::SavePackage(Package, NewFlipbook, EObjectFlags::RF_Public | EObjectFlags::RF_Standalone, *PackageFileName, GError, nullptr);
		} else {
			if (GEngine)
				GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, AssetName);
		}
	}
}

void UAnimatedTileMaker::CreateEmoteSet(const FString& FrameDirectory, const FString& SourceTexture, const int& CharacterIndex) {
	static FString Directions[] = { TEXT("Nod"), TEXT("Shake"), TEXT("Laugh"), TEXT("Scared") };
	for (int i = 0; i < 4; i++) {
		// Initialize the Name of the New Flipbook
		FString FlipbookName = SourceTexture + TEXT("_") + FString::FromInt(CharacterIndex);
		FString DestinationName = SourceTexture + TEXT("_") + FString::FromInt(CharacterIndex) + TEXT("_Emote") + Directions[i];
		FString DestinationDirectory = FrameDirectory + TEXT("Emote/");

		// Initialize Directory
		FString PackageName = TEXT("/Game/") + DestinationDirectory;
		PackageName += DestinationName;
		UPackage* Package = CreatePackage(NULL, *PackageName);
		Package->FullyLoad();

		FString AssetName = PackageName + TEXT(".") + DestinationName;
		if (LoadObject<UObject>(NULL, *AssetName) == nullptr) {
			// Edit the contents of the flipbook
			UPaperFlipbook* NewFlipbook = NewObject<UWrittingFlipbook>(Package, *DestinationName, RF_Public | RF_Standalone | RF_MarkAsRootSet);
			NewFlipbook->AddToRoot();
			TArray<FString> FrameNames;
			FrameNames.Add(FlipbookName + TEXT("_") + FString::FromInt(i * 3 + 1));
			FrameNames.Add(FlipbookName + TEXT("_") + FString::FromInt(i * 3 + 0));
			FrameNames.Add(FlipbookName + TEXT("_") + FString::FromInt(i * 3 + 1));
			FrameNames.Add(FlipbookName + TEXT("_") + FString::FromInt(i * 3 + 2));
			TArray<FPaperFlipbookKeyFrame> KeyFrames;
			for (FString Name : FrameNames) {
				FString FileName = TEXT("/Game/") + FrameDirectory + TEXT("/") + Name + TEXT(".") + Name;
				FPaperFlipbookKeyFrame KeyFrame;
				KeyFrame.FrameRun = 1;
				KeyFrame.Sprite = LoadObject<UPaperSprite>(NULL, *FileName);
				if (KeyFrame.Sprite == nullptr) {
					if (GEngine)
						GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FileName);
				} else {
					if (GEngine)
						GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FileName);
				}
				KeyFrames.Add(KeyFrame);
			}
			Cast<UWrittingFlipbook>(NewFlipbook)->SetKeyFrames(KeyFrames);

			// Save the flipbook
			FString PackageFileName = FPackageName::LongPackageNameToFilename(PackageName, FPackageName::GetAssetPackageExtension());
			bool bSaved = UPackage::SavePackage(Package, NewFlipbook, EObjectFlags::RF_Public | EObjectFlags::RF_Standalone, *PackageFileName, GError, nullptr);
		} else {
			if (GEngine)
				GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, AssetName);
		}
	}
}

void UAnimatedTileMaker::CreateAnimation(const FString& FrameDirectory, const FString& CharacterName, const int& AnimationIndex) {
	// Initialize the Name of the New Flipbook
	FString FlipbookName = TEXT("animation") + FString::FromInt(AnimationIndex) + TEXT("_") + CharacterName;
	FString DestinationDirectory = FrameDirectory + TEXT("Emote/");

	// Initialize Directory
	FString PackageName = TEXT("/Game/") + DestinationDirectory + TEXT("/");
	PackageName += FlipbookName;
	UPackage* Package = CreatePackage(NULL, *PackageName);
	Package->FullyLoad();

	FString AssetName = PackageName + TEXT(".") + FlipbookName;
	if (LoadObject<UObject>(NULL, *AssetName) == nullptr) {
		// Edit the contents of the flipbook
		UPaperFlipbook* NewFlipbook = NewObject<UWrittingFlipbook>(Package, *FlipbookName, RF_Public | RF_Standalone | RF_MarkAsRootSet);
		NewFlipbook->AddToRoot();
		TArray<FString> FrameNames;
		FrameNames.Add(FlipbookName + TEXT("_") + FString::FromInt(1));
		FrameNames.Add(FlipbookName + TEXT("_") + FString::FromInt(0));
		FrameNames.Add(FlipbookName + TEXT("_") + FString::FromInt(1));
		FrameNames.Add(FlipbookName + TEXT("_") + FString::FromInt(2));
		TArray<FPaperFlipbookKeyFrame> KeyFrames;
		for (FString Name : FrameNames) {
			FString FileName = TEXT("/Game/") + FrameDirectory + TEXT("/") + Name + TEXT(".") + Name;
			FPaperFlipbookKeyFrame KeyFrame;
			KeyFrame.FrameRun = 1;
			KeyFrame.Sprite = LoadObject<UPaperSprite>(NULL, *FileName);
			if (KeyFrame.Sprite == nullptr) {
				if (GEngine)
					GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FileName);
			} else {
				if (GEngine)
					GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FileName);
			}
			KeyFrames.Add(KeyFrame);
		}
		Cast<UWrittingFlipbook>(NewFlipbook)->SetKeyFrames(KeyFrames);

		// Save the flipbook
		FString PackageFileName = FPackageName::LongPackageNameToFilename(PackageName, FPackageName::GetAssetPackageExtension());
		bool bSaved = UPackage::SavePackage(Package, NewFlipbook, EObjectFlags::RF_Public | EObjectFlags::RF_Standalone, *PackageFileName, GError, nullptr);
	} else {
		if (GEngine)
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, AssetName);
	}
}

void UAnimatedTileMaker::CreateBattleSprites(const FString FrameDirectory, const FString CharacterName) {
	static FString Actions[] = {
		TEXT("Idle"), TEXT("AttackA"), TEXT("Escape"),
		TEXT("Ready"), TEXT("AttackB"), TEXT("Victory"),
		TEXT("Cast"), TEXT("Bow"), TEXT("Danger"),
		TEXT("Guard"), TEXT("PhysicalSkill"), TEXT("Statused"),
		TEXT("Damage"), TEXT("Spell"), TEXT("Asleep"),
		TEXT("Evade"), TEXT("UseItem"), TEXT("Dead")
	};

	for (int i = 0; i < 18; i++) {
		// Initialize the Name of the New Flipbook
		FString FlipbookName = CharacterName + TEXT("_Battle_Sprite");
		FString DestinationName = CharacterName + TEXT("_") + Actions[i];
		FString DestinationDirectory = FrameDirectory + TEXT("Actions/");

		// Initialize Directory
		FString PackageName = TEXT("/Game/") + DestinationDirectory;
		PackageName += DestinationName;
		UPackage* Package = CreatePackage(NULL, *PackageName);
		Package->FullyLoad();

		FString AssetName = PackageName + TEXT(".") + FlipbookName;
		if (LoadObject<UObject>(NULL, *AssetName) == nullptr) {
			// Edit the contents of the flipbook
			UPaperFlipbook* NewFlipbook = NewObject<UWrittingFlipbook>(Package, *DestinationName, RF_Public | RF_Standalone | RF_MarkAsRootSet);
			NewFlipbook->AddToRoot();
			TArray<FString> FrameNames;
			switch (i) {
			case 0: // Idle
			case 2: // Escape
			case 3: // Ready
			case 5: // Victory
			case 6: // Cast
			case 8: // Danger
			case 9: // Guard
			case 11: // Statused
			case 14: // Asleep
				FrameNames.Add(FlipbookName + TEXT("_") + FString::FromInt(i * 3 + 1));
				break;
			}
			FrameNames.Add(FlipbookName + TEXT("_") + FString::FromInt(i * 3 + 0));
			FrameNames.Add(FlipbookName + TEXT("_") + FString::FromInt(i * 3 + 1));
			FrameNames.Add(FlipbookName + TEXT("_") + FString::FromInt(i * 3 + 2));

			TArray<FPaperFlipbookKeyFrame> KeyFrames;
			for (FString Name : FrameNames) {
				FString FileName = TEXT("/Game/") + FrameDirectory + Name + TEXT(".") + Name;
				FPaperFlipbookKeyFrame KeyFrame;
				KeyFrame.FrameRun = 1;
				KeyFrame.Sprite = LoadObject<UPaperSprite>(NULL, *FileName);
				if (KeyFrame.Sprite == nullptr) {
					if (GEngine)
						GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FileName);
				} else {
					if (GEngine)
						GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FileName);
				}
				KeyFrames.Add(KeyFrame);
			}
			Cast<UWrittingFlipbook>(NewFlipbook)->SetKeyFrames(KeyFrames);

			// Save the flipbook
			FString PackageFileName = FPackageName::LongPackageNameToFilename(PackageName, FPackageName::GetAssetPackageExtension());
			bool bSaved = UPackage::SavePackage(Package, NewFlipbook, EObjectFlags::RF_Public | EObjectFlags::RF_Standalone, *PackageFileName, GError, nullptr);
		} else {
			if (GEngine)
				GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, AssetName);
		}
	}
}
