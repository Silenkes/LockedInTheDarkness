#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "LITDCharacter.generated.h"

struct FInputActionValue;
class UCameraComponent;

UCLASS()
class LOCKEDINTHEDARKNESS_API ALITDCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	ALITDCharacter();

	UCameraComponent* GetViewCamera() const { return ViewCamera; }

	virtual void Tick(float DeltaTime) override;
	virtual void Jump() override;

	void Move(const FInputActionValue& Value);
	void Look(const FInputActionValue& Value);
	void CrouchPressed();
	void CrouchReleased();
	
protected:
	virtual void BeginPlay() override;

	UFUNCTION()
	void OnCapsuleBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnCapsuleEndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

private:
	UPROPERTY(EditAnywhere, Category = "Camera")
	UCameraComponent* ViewCamera;
	
	float CameraSensitivityMultiplier = 1.f;
};
