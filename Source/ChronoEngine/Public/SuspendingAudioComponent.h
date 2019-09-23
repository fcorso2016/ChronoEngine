// Created by Francesco Corso. Labeled for reuse with attribution under Creative Commons.

#pragma once

#include "CoreMinimal.h"
#include "Components/AudioComponent.h"
#include "SuspendingAudioComponent.generated.h"

/**
 * An audio component that has the capacity to pause and resume from it's current position
 */
UCLASS()
class CHRONOENGINE_API USuspendingAudioComponent : public UAudioComponent {
	GENERATED_BODY()

private:
	/**
	 * Should the game start by playing at the start of the game
	 */
	UPROPERTY(EditAnywhere, Category = Sound)
	bool bStartPlaying;

	/**
	 * The current time the sound has been playing for
	 */
	UPROPERTY()
	float CurrentTime;

public:
	USuspendingAudioComponent(const FObjectInitializer& ObjectInitializer);
	void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	void Play(float StartTime) override;
	void Stop() override;

	/**
	 * Pause the audio saving it's current position
	 */
	UFUNCTION(BlueprintCallable, Category = Sound)
	virtual void Pause();

	/**
	 * Resume the paused audio
	 */
	UFUNCTION(BlueprintCallable, Category = Sound)
	virtual void Resume();
	
};
