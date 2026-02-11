#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "InteractionInterface.generated.h"

UINTERFACE(MinimalAPI)
class UInteractionInterface : public UInterface
{
	GENERATED_BODY()
};

class LOCKEDINTHEDARKNESS_API IInteractionInterface
{
	GENERATED_BODY()

public:
	virtual void Interact(ACharacter* Character) = 0;
	virtual void EndInteract(ACharacter* Character) = 0;
};
