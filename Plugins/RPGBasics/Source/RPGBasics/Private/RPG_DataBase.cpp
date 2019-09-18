// Created by Francesco Corso. Labeled for reuse with attribution under Creative Commons.


#include "RPG_DataBase.h"

void URPG_DataBase::PostEditChangeProperty(struct FPropertyChangedEvent& PropertyChangedEvent) {
	Super::PostEditChangeProperty(PropertyChangedEvent);
	ValidatePropertyInformation();
}
