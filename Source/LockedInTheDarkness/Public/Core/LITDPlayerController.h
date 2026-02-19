#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "Interfaces/EnhancedInputBindingProvider.h"
#include "LITDPlayerController.generated.h"

class UInputMappingContext;
class UInputAction;
class ALITDCharacter;

UCLASS()
class LOCKEDINTHEDARKNESS_API ALITDPlayerController : public APlayerController, public IEnhancedInputBindingProvider
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;
	virtual void OnPossess(APawn* InPawn) override;
	virtual FKey GetBindingKey(EInputActionType ActionType) const override;

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

	UPROPERTY(EditAnywhere, Category = "Input Action")
	UInputAction* InteractAction;

	UPROPERTY()
	ALITDCharacter* ControlledCharacter;

	void BindEnhancedInputComponent();
};
