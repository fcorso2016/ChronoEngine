// Created by Francesco Corso. Labeled for reuse with attribution under Creative Commons.


#include "ChronoCodeUtilities.h"

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
