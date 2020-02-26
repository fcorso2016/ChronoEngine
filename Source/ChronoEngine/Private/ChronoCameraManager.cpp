// Created by Francesco Corso. Labeled for reuse with attribution under Creative Commons.


#include "ChronoCameraManager.h"

void AChronoCameraManager::SetPlayerCharacter(APawn* NewPlayer) {
	SetViewTarget(NewPlayer);
}
