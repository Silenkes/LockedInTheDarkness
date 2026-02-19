#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interfaces/InteractionInterface.h"
#include "InteractableObject.generated.h"

class UBoxComponent;

UENUM(BlueprintType)
enum class EInteractionType : uint8
{
	EIT_None UMETA(DisplayName = "None"),
	EIT_Open UMETA(DisplayName = "Open"),
	EIT_Activate UMETA(DisplayName = "Activate"),
	EIT_PickUp UMETA(DisplayName = "Pick Up"),
};

UENUM(BlueprintType)
enum class EOpeningObjectType : uint8
{
	EOOT_None UMETA(DisplayName = "None"),
	EOOT_InteriorDoor UMETA(DisplayName = "Interior door"),
	EOOT_BigDoor UMETA(DisplayName = "Big Door"),
};

UENUM(BlueprintType)
enum class EActivatableObjectType : uint8
{
	EAOT_None UMETA(DisplayName = "None"),
	EAOT_Button UMETA(DisplayName = "Button"),
	EAOT_Statue UMETA(DisplayName = "Statue"),
	EAOT_Lever UMETA(DisplayName = "Lever"),
};

UENUM(BlueprintType)
enum class EPickUpType : uint8
{
	EPUT_None UMETA(DisplayName = "None"),
	EPUT_Key UMETA(DisplayName = "Key"),
	EPUT_Weapon UMETA(DisplayName = "Weapon"),
};

UCLASS()
class LOCKEDINTHEDARKNESS_API AInteractableObject : public AActor, public IInteractionInterface
{
	GENERATED_BODY()
	
public:	
	AInteractableObject();
	virtual void Tick(float DeltaTime) override;

protected:
	virtual void BeginPlay() override;
	virtual void Interact(ACharacter* Character) override;
	virtual FObjectData GetInteractionData() const override { return ObjectData; }

	void OpenInteriorDoor();
	void OpenBigDoor();
	void ActivateButton();
	void ActivateStatue();
	void ActivateLever();
	void PickUpKey();
	void PickUpWeapon();

private:
	
	UPROPERTY(EditAnywhere, Category = "Type")
	EInteractionType InteractionType = EInteractionType::EIT_None;

	// * Choose what need to open
	UPROPERTY(EditAnywhere, Category = "Type", meta = (EditCondition = "InteractionType == EInteractionType::EIT_Open", EditConditionHides))
	EOpeningObjectType OpeningObjectType = EOpeningObjectType::EOOT_None;

	// * Choose what need to activate
	UPROPERTY(EditAnywhere, Category = "Type", meta = (EditCondition = "InteractionType == EInteractionType::EIT_Activate", EditConditionHides))
	EActivatableObjectType ActivatableObjectType = EActivatableObjectType::EAOT_None;

	// * Choose what need to pick up
	UPROPERTY(EditAnywhere, Category = "Type", meta = (EditCondition = "InteractionType == EInteractionType::EIT_PickUp", EditConditionHides))
	EPickUpType PickUpType = EPickUpType::EPUT_None;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	USceneComponent* SceneRoot;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	UBoxComponent* BoxCollision;

	UPROPERTY(EditAnywhere, Category = "Components")
	UStaticMeshComponent* StaticMesh;

	UPROPERTY(EditAnywhere, Category = "Interaction")
	FObjectData ObjectData;
};
