#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Interfaces/InteractionTargetingInterface.h"
#include "ReticleWidget.generated.h"

class UImage;

UCLASS()
class LOCKEDINTHEDARKNESS_API UReticleWidget : public UUserWidget, public IInteractionTargetingInterface
{
	GENERATED_BODY()
	
protected:
	virtual void NativePreConstruct() override;
	virtual void NativeConstruct() override;
	virtual void OnTargeted(const FInteractionTargetingData& TargetingData) override;

private:
	UPROPERTY(meta = (BindWidgetOptional))
	UImage* ImageReticle;

	UPROPERTY(EditAnywhere, Category = "Reticle Appearance")
	FLinearColor ReticleDefaultColor = FLinearColor::White;

	UPROPERTY(EditAnywhere, Category = "Reticle Appearance")
	FLinearColor ReticleTargetingColor = FLinearColor::Red;
};
