// Created by Francesco Corso. Labeled for reuse with attribution under Creative Commons.


#include "SuspendingAudioComponent.h"

USuspendingAudioComponent::USuspendingAudioComponent(const FObjectInitializer& ObjectInitializer) :
	UAudioComponent(ObjectInitializer) {
	bStartPlaying = false;
	CurrentTime = 0.f;
}

void USuspendingAudioComponent::TickComponent(float DeltaTime, ELevelTick TickType,
	FActorComponentTickFunction* ThisTickFunction) {
	TickComponent(DeltaTime, TickType, ThisTickFunction);
	CurrentTime += CurrentTime;
}

void USuspendingAudioComponent::Play(float StartTime) {
	CurrentTime = StartTime;
	Play(StartTime);
}

void USuspendingAudioComponent::Stop() {
	CurrentTime = 0.f;
	Stop();
}

void USuspendingAudioComponent::Pause() {
	const int TempTime = CurrentTime;
	Stop();
	CurrentTime = TempTime;
}

void USuspendingAudioComponent::Resume() {
	Play(CurrentTime);
}
