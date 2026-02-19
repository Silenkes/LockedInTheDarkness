#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "LITDCharacter.generated.h"

struct FInputActionValue;
class UCameraComponent;
class UCharacterInteractionComponent;

UCLASS()
class LOCKEDINTHEDARKNESS_API ALITDCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	ALITDCharacter();

	UFUNCTION(BlueprintCallable, Category = "Camera")
	UCameraComponent* GetViewCamera() const { return ViewCamera; }

	virtual void Tick(float DeltaTime) override;
	virtual void Jump() override;

	void Move(const FInputActionValue& Value);
	void Look(const FInputActionValue& Value);
	void OnCrouch();
	void OnUnCrouch();
	void Interact();

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditAnywhere, Category = "Camera")
	UCameraComponent* ViewCamera;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Interaction", meta = (AllowPrivateAccess = "true"))
	UCharacterInteractionComponent* InteractionComponent;

	float CameraSensitivityMultiplier = 1.f;
};
