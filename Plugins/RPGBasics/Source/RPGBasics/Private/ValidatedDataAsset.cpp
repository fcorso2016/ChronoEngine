// Created by Francesco Corso. Labeled for reuse with attribution under Creative Commons.


#include "ValidatedDataAsset.h"

void UValidatedDataAsset::PostEditChangeProperty(struct FPropertyChangedEvent& PropertyChangedEvent) {
	Super::PostEditChangeProperty(PropertyChangedEvent);
	ValidatePropertyInformation();
}