// Fill out your copyright notice in the Description page of Project Settings.


#include "ChronoEngineGameModeBase.h"

FName AChronoEngineGameModeBase::GetDebugStartMap() const {
	AChronoWorldSettings* WorldSettings = Cast<AChronoWorldSettings>(GetWorldSettings());
	if (WorldSettings != nullptr) {
		return WorldSettings->DebugStartMap;
	}

	return FName();
}
