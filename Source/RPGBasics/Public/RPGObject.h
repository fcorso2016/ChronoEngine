// Created by Francesco Corso. Labeled for reuse with attribution under Creative Commons.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Engine/GameInstance.h"
#include "RPGObject.generated.h"

/**
 * Basic object class that contains a few more additional functionalities
 */
UCLASS(abstract, Blueprintable, meta = (DisplayName = "RPG Object"))
class RPGBASICS_API URPGObject : public UObject {
	GENERATED_BODY()
	
protected:
	/**
	 * The reference to the game instance object stored by the game in order to access the object when needed
	 */
	UPROPERTY(BlueprintReadOnly, Category = Context)
	UGameInstance* GameInstance;

public:
	void PostInitProperties() override;

	/**
	 * Initialize the object from the constructor
	 */
	UFUNCTION(BlueprintImplementableEvent, Category = Construction)
	void Initialize();

protected:
	/**
	 * Set the reference to the game instance object
	 * @param GameInstanceObject the game instance object for the game
	 */
	UFUNCTION(BlueprintCallable, Category = Construction)
	void SetGameInstance(UGameInstance* GameInstanceObject);

};
