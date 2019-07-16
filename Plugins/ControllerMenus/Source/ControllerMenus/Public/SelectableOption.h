// Created by Francesco Corso. Labeled for reuse with attribution under Creative Commons.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Runtime/UMG/Public/Components/Button.h"
#include "SelectableOption.generated.h"

/**
 * An option within a cursored window that players can select
 */
UCLASS(Blueprintable)
class CONTROLLERMENUS_API USelectableOption : public UUserWidget {
	GENERATED_BODY()

public:
	/**
	 * The button the window uses for interactivity
	 */
	UPROPERTY(BlueprintReadOnly, Category = Components, meta = (BindWidget))
	UButton* Interactable;

	/**
	 * The window that owns this element
	 */
	UPROPERTY(BlueprintReadOnly, Category = Input)
	class UCursoredWindow* Owner;

	/**
	 * The reference symbol of this element in the window
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Input)
	FName Symbol;

protected:
	TSharedRef<SWidget> RebuildWidget() override;

private:
	/**
	 * Change the selection of the owning window to this element
	 */
	UFUNCTION()
	void SelectElement();

	/**
	 * Used to invoke selection functionality
	 */
	UFUNCTION()
	void ClickElement();
	
};
