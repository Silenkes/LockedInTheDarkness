#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "LITDPlayerController.generated.h"

class ALITDCharacter;
class UInputMappingContext;
class UInputAction;

UCLASS()
class LOCKEDINTHEDARKNESS_API ALITDPlayerController : public APlayerController
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;
	virtual void OnPossess(APawn* InPawn) override;

private:
	UPROPERTY(EditAnywhere, Category = "Input Action")
	UInputMappingContext* InputMappingContext;

	UPROPERTY(EditAnywhere, Category = "Input Action")
	UInputAction* MoveAction;

	UPROPERTY(EditAnywhere, Category = "Input Action")
	UInputAction* LookAction;

	UPROPERTY(EditAnywhere, Category = "Input Action")
	UInputAction* JumpAction;

	UPROPERTY(EditAnywhere, Category = "Input Action")
	UInputAction* CrouchAction;

	UPROPERTY()
	ALITDCharacter* ControlledCharacter;

	void BindEnhancedInputComponent();
};
