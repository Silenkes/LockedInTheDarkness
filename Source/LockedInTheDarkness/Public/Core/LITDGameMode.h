#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "LITDGameMode.generated.h"

UCLASS()
class LOCKEDINTHEDARKNESS_API ALITDGameMode : public AGameModeBase
{
	GENERATED_BODY()
	
protected:
	virtual void BeginPlay() override;
};
