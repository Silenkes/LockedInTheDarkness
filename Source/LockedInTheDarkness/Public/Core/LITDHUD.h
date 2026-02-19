// * This is the widgets manager class

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "LITDHUD.generated.h"

struct FInteractionTargetingData;

UENUM(BlueprintType)
enum class EWidgetId : uint8
{
	EWI_None UMETA(DisplayName = "None"),
	EWI_Reticle UMETA(DisplayName = "Reticle"),
	EWI_InteractionHint UMETA(DisplayName = "Interaction hint"),
};

UCLASS()
class LOCKEDINTHEDARKNESS_API ALITDHUD : public AHUD
{
	GENERATED_BODY()
	
public:
	UUserWidget* AddWidget(EWidgetId WidgetId);
	void ShowWidget(EWidgetId WidgetId);
	void HideWidget(EWidgetId WidgetId);
	void SetInteractionWidgetData(EWidgetId WidgetId, const FInteractionTargetingData& Data);
	void RemoveWidget(EWidgetId WidgetId);

	// * Removes last created widget, be careful with this!
	void RemoveLastWidget();

private:
	UPROPERTY(EditDefaultsOnly, Category = Widgets)
	TMap<EWidgetId, TSubclassOf<UUserWidget>> WidgetClasses;

	UPROPERTY()
	UUserWidget* LastCreatedWidget = nullptr;

	UPROPERTY()
	TMap<EWidgetId, UUserWidget*> CreatedWidgets;
};
