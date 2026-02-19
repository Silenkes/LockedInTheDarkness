#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "EnhancedInputBindingProvider.generated.h"

UINTERFACE(MinimalAPI)
class UEnhancedInputBindingProvider : public UInterface
{
	GENERATED_BODY()
};

enum class EInputActionType : uint8
{
	EIAT_Move,
	EIAT_Look,
	EIAT_Jump,
	EIAT_Crouch,
	EIAT_Interact,
};

class LOCKEDINTHEDARKNESS_API IEnhancedInputBindingProvider
{
	GENERATED_BODY()

public:
	virtual FKey GetBindingKey(EInputActionType ActionType) const = 0;
};
