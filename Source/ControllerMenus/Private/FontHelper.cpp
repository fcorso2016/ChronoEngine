// Created by cygon and IridiumStudios on the Unreal Engine forums.


#include "FontHelper.h"
#include "SlateApplication.h"
#include "Fonts/FontMeasure.h"
#include "IOS/IOSPlatformTextField.h"

FVector2D UFontHelper::MeasureString(UTextBlock* TextBlock, const FString& Text ) {
    TSharedRef<FSlateFontMeasure> FontMeasureService = (
        FSlateApplication::Get().GetRenderer()->GetFontMeasureService()
        );

    return FontMeasureService->Measure(Text, TextBlock->Font);
}

FVector2D UFontHelper::MeasureWrappedString(UTextBlock* TextBlock, const FString& Text, float WrapWidth, float LinePercentageHeight) {
    FVector2D Size(0.0f, 0.0f);

    // Everything we do here duplicates what FSlateFontMeasure::MeasureStringInternal()
  // already does. Sadly, the existing method is private and there's no exposed method
  // that happens to call it in a way we can work with...

  // Scan the entire string, keeping track of where lines begin and checking every time
  // a whitespace is encountered how long the line would be when wrapped there.
  // We could do this in a more fancy way with binary search and by guessing lengths,
  // but it's typically done just one when new text is displayed, so this is good enough.
    {
        TSharedRef<FSlateFontMeasure> FontMeasureService = (
            FSlateApplication::Get().GetRenderer()->GetFontMeasureService()
            );

        int32 LineCount = 1;
        bool bLastWasWhitespace = true;

        bool foundLineStartIndex = false;
        int32 LineStartIndex = 0;

        int32 LastGoodWrapIndex = -1;
        float LastGoodWrapWidth = 0.0f;

        // Scanning loop, steps through the string character by character
        int32 TextLength = text.Len();
        for (int32 Index = 0; Index < TextLength; ++Index) {

            // Check if the current character is a whitespace character (and thus, the line
            // can be broken at this point)
            TCHAR Character = text[Index];
            bool bIsWhitespace = (
                (Character == TEXT(' ')) || (Character == TEXT('\t')) || (Character == TEXT('\n'))
                );

            // If we have a line start index (meaning there was a non-whitespace character),
            // do the line break checking
            if (foundLineStartIndex) {

                // Don't re-check line breaks on consecutive whitespaces
                if (bIsWhitespace && bLastWasWhitespace) {
                    continue;
                }
                bLastWasWhitespace = bIsWhitespace;

                // If this is no whitespace, we can't wrap here, so continue scanning
                if (!bIsWhitespace) {
                    continue;
                }

                // Measure the line up until the whitespace we just encountered
                FVector2D potentialLineSize = FontMeasureService->Measure(
                    text, LineStartIndex, Index - 1, TextBlock->Font, false
                );

                // If it still fits in the line, remember this as the most recent good wrap ppoint
                if (potentialLineSize.X < WrapWidth) {
                    LastGoodWrapIndex = Index;
                    LastGoodWrapWidth = potentialLineSize.X;
                } else {
                    ++LineCount;

                    if (LastGoodWrapIndex == -1) { // First whitespace and it's already too long...
                        Size.X = FMath::Max(Size.X, potentialLineSize.X);
                    } else { // Phew... we have a good wrapping position remembered
                        Size.X = FMath::Max(Size.X, LastGoodWrapWidth);
                    }

                    // Reset all trackers to scan for a new line from here
                    LastGoodWrapIndex = -1;
                    LineStartIndex = Index;
                    foundLineStartIndex = false;
                }

            } else if (!bIsWhitespace) {
                foundLineStartIndex = true; // The first non-whitespace character marks the line start
                LineStartIndex = Index;
            }

        } // for

        // If there are characters remaining on the last line, measure them, too
        // (we also know it doesn't end in a space/newline because otherwise this
        // property would have a value of false, thus this final check is really basic)
        if (foundLineStartIndex) {
            FVector2D FinalLineSize = FontMeasureService->Measure(
                text, LineStartIndex, TextLength - 1, TextBlock->Font, false
            );
            Size.X = FMath::Max(Size.X, FinalLineSize.X);
        }

        Size.Y = (
            static_cast<float>(FontMeasureService->GetMaxCharacterHeight(TextBlock->Font))* LineCount
            );
    }

    return Size;
}