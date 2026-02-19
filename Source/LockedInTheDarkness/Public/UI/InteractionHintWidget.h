#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Interfaces/InteractionTargetingInterface.h"
#include "InteractionHintWidget.generated.h"

class UTextBlock;

UCLASS()
class LOCKEDINTHEDARKNESS_API UInteractionHintWidget : public UUserWidget, public IInteractionTargetingInterface
{
	GENERATED_BODY()
	
protected:
	virtual void OnTargeted(const FInteractionTargetingData& TargetingData) override;

private:
	UPROPERTY(meta = (BindWidgetOptional))
	UTextBlock* TextObjectName;

	UPROPERTY(meta = (BindWidgetOptional))
	UTextBlock* TextInteraction;

	UPROPERTY(meta = (BindWidgetOptional))
	UTextBlock* TextInteractionKey;
};