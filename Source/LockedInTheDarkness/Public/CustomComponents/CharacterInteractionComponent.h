#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CharacterInteractionComponent.generated.h"

class UCameraComponent;
class ALITDHUD;

UCLASS( ClassGroup=(Interaction), meta=(BlueprintSpawnableComponent) )
class LOCKEDINTHEDARKNESS_API UCharacterInteractionComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UCharacterInteractionComponent();

	void Initialize(UCameraComponent* CameraComponent);

	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void OnInteract();

protected:
	virtual void BeginPlay() override;

	UFUNCTION()
	void OnCapsuleBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnCapsuleEndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	void SearchingForInteractables();

private:
	UPROPERTY()
	ACharacter* OwnerCharacter;

	UPROPERTY()
	UCameraComponent* OwnerCamera;

	UPROPERTY()
	TArray<AActor*> NearbyInteractables; // * Array to store nearby interactable actors for Overlap and EndOverlap events

	UPROPERTY()
	AActor* LastInteractionTarget;

	UPROPERTY()
	ALITDHUD* WidgetsManager;

	bool bInteractablesNearby;
};
