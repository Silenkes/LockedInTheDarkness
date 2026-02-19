#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "InteractionInterface.generated.h"

USTRUCT()
struct FObjectData
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	FText Name;

	// * This variable should contain action text that will be shown when player will target this object
	UPROPERTY(EditAnywhere)
	FText InteractionText;
};

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
	virtual FObjectData GetInteractionData() const = 0;
};
