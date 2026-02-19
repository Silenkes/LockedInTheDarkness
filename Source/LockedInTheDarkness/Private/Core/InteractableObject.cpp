#include "Core/InteractableObject.h"
#include "Components/BoxComponent.h"

AInteractableObject::AInteractableObject()
{
	PrimaryActorTick.bCanEverTick = false;

	SceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("SceneRoot"));
	RootComponent = SceneRoot;
	BoxCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxCollision"));
	BoxCollision->SetupAttachment(SceneRoot);
	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	StaticMesh->SetupAttachment(SceneRoot);
}

void AInteractableObject::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AInteractableObject::BeginPlay()
{
	Super::BeginPlay();
	
}

void AInteractableObject::Interact(ACharacter* Character)
{
	switch (InteractionType)
	{
	case EInteractionType::EIT_None:
		UE_LOG(LogTemp, Warning, TEXT("Interacted with %s, but it has None InteractionType!"), *GetName());
		break;

	case EInteractionType::EIT_Open:
		switch (OpeningObjectType) 
		{
		case EOpeningObjectType::EOOT_None:
			UE_LOG(LogTemp, Warning, TEXT("Interacted with %s, but it has None OpeningObjectType!"), *GetName());
			break;

		case EOpeningObjectType::EOOT_InteriorDoor:
			OpenInteriorDoor();
			break;

		case EOpeningObjectType::EOOT_BigDoor:
			OpenBigDoor();
			break;

		default:
			break;
		}
		break;

	case EInteractionType::EIT_Activate:
		switch (ActivatableObjectType)
		{
		case EActivatableObjectType::EAOT_None:
			UE_LOG(LogTemp, Warning, TEXT("Interacted with %s, but it has None ActivatableObjectType!"), *GetName());
			break;

		case EActivatableObjectType::EAOT_Button:
			ActivateButton();
			break;

		case EActivatableObjectType::EAOT_Statue:
			ActivateStatue();
			break;

		case EActivatableObjectType::EAOT_Lever:
			ActivateLever();
			break;

		default:
			break;
		}
		break;
			
	case EInteractionType::EIT_PickUp:
		switch (PickUpType)
		{
		case EPickUpType::EPUT_None:
			UE_LOG(LogTemp, Warning, TEXT("Interacted with %s, but it has None PickUpType!"), *GetName());
			break;

		case EPickUpType::EPUT_Key:
			PickUpKey();
			break;

		case EPickUpType::EPUT_Weapon:
			PickUpWeapon();
			break;

		default:
			break;
		}
		break;

	default:
		break;
	}
}

void AInteractableObject::OpenInteriorDoor()
{
	UE_LOG(LogTemp, Warning, TEXT("Opened interior door %s!"), *GetName());
}

void AInteractableObject::OpenBigDoor()
{
	UE_LOG(LogTemp, Warning, TEXT("Opened Big Door %s!"), *GetName());
}

void AInteractableObject::ActivateButton()
{
	UE_LOG(LogTemp, Warning, TEXT("Activated button %s!"), *GetName());
}

void AInteractableObject::ActivateStatue()
{
	UE_LOG(LogTemp, Warning, TEXT("Activated statue %s!"), *GetName());
}

void AInteractableObject::ActivateLever()
{
	UE_LOG(LogTemp, Warning, TEXT("Activated lever %s!"), *GetName());
}

void AInteractableObject::PickUpKey()
{
	UE_LOG(LogTemp, Warning, TEXT("Picked up key %s!"), *GetName());
}

void AInteractableObject::PickUpWeapon()
{
	UE_LOG(LogTemp, Warning, TEXT("Picked up weapon %s!"), *GetName());
}
