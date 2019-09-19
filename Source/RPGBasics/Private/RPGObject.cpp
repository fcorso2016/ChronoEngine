// Created by Francesco Corso. Labeled for reuse with attribution under Creative Commons.


#include "RPGObject.h"

void URPGObject::PostInitProperties() {
	Super::PostInitProperties();
	Initialize();
}

void URPGObject::SetGameInstance(UGameInstance* GameInstanceObject) {
	GameInstance = GameInstanceObject;
}
