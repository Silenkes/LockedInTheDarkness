#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "InteractionTargetingInterface.generated.h"

UENUM()
enum class EWidgetColorType : uint8
{
	EWCT_Default,
	EWCT_Targeting,
};

struct FInteractionTargetingData
{
	FText TargetName;
	FText TargetInteractionText;
	FText InteractionKeyText;
	EWidgetColorType WidgetColorType = EWidgetColorType::EWCT_Default;
};

UINTERFACE(MinimalAPI)
class UInteractionTargetingInterface : public UInterface
{
	GENERATED_BODY()
};

class LOCKEDINTHEDARKNESS_API IInteractionTargetingInterface
{
	GENERATED_BODY()

public:
	virtual void OnTargeted(const FInteractionTargetingData& TargetingData) = 0;
};
