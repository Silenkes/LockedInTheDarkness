#include "CustomComponents/CharacterInteractionComponent.h"
#include "Interfaces/InteractionInterface.h"
#include "Interfaces/InteractionTargetingInterface.h"
#include "Interfaces/EnhancedInputBindingProvider.h"
#include "Components/CapsuleComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"
#include "Core/LITDHUD.h"

UCharacterInteractionComponent::UCharacterInteractionComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UCharacterInteractionComponent::Initialize(UCameraComponent* CameraComponent)
{
	OwnerCamera = CameraComponent;
}

void UCharacterInteractionComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (bInteractablesNearby && OwnerCamera)
		SearchingForInteractables();
}

void UCharacterInteractionComponent::BeginPlay()
{
	Super::BeginPlay();

	OwnerCharacter = Cast<ACharacter>(GetOwner());
	WidgetsManager = Cast<ALITDHUD>(UGameplayStatics::GetPlayerController(GetWorld(), 0)->GetHUD());

	if (UCapsuleComponent* Capsule = OwnerCharacter->GetCapsuleComponent())
	{
		Capsule->OnComponentBeginOverlap.AddDynamic(this, &UCharacterInteractionComponent::OnCapsuleBeginOverlap);
		Capsule->OnComponentEndOverlap.AddDynamic(this, &UCharacterInteractionComponent::OnCapsuleEndOverlap);
	}

	if (WidgetsManager)
	{
		WidgetsManager->AddWidget(EWidgetId::EWI_InteractionHint);
		WidgetsManager->HideWidget(EWidgetId::EWI_InteractionHint);
	}
}

void UCharacterInteractionComponent::OnCapsuleBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor && OtherActor->Implements<UInteractionInterface>())
	{
		bInteractablesNearby = true;
		NearbyInteractables.Add(OtherActor);
	}
}

void UCharacterInteractionComponent::OnCapsuleEndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (OtherActor && OtherActor->Implements<UInteractionInterface>())
	{
		NearbyInteractables.Remove(OtherActor);

		if (NearbyInteractables.Num() == 0)
		{
			bInteractablesNearby = false;
			LastInteractionTarget = nullptr;

			if (WidgetsManager)
			{
				WidgetsManager->HideWidget(EWidgetId::EWI_InteractionHint); // hint hides
				WidgetsManager->SetInteractionWidgetData(EWidgetId::EWI_Reticle, FInteractionTargetingData{ .WidgetColorType = EWidgetColorType::EWCT_Default });
			}
		}
	}
}

void UCharacterInteractionComponent::SearchingForInteractables()
{
	// Parameters
	FVector Start = OwnerCamera->GetComponentLocation();
	FVector ForwardVector = OwnerCamera->GetComponentRotation().Vector();
	FVector End = ForwardVector * 300.f + Start;
	FHitResult HitResult;
	FCollisionQueryParams CollisionParams;

	// Objects to ignore
	CollisionParams.AddIgnoredActor(OwnerCharacter);

	bool bHit = GetWorld()->LineTraceSingleByChannel(HitResult, Start, End, ECC_Visibility, CollisionParams);

	if (bHit)
	{
		AActor* HitActor = HitResult.GetActor();

		if (HitActor != LastInteractionTarget)
		{
			if (IInteractionInterface* InteractionInterface = Cast<IInteractionInterface>(HitActor))
			{
				if (WidgetsManager)
				{
					FObjectData InteractionData = InteractionInterface->GetInteractionData();
					FText InteractionKeyText;

					if (OwnerCharacter)
						if(const AController* OwnerController = OwnerCharacter->GetController())
							if (const IEnhancedInputBindingProvider* BindingInterface = Cast<IEnhancedInputBindingProvider>(OwnerController))
							{
								FKey InteractionKey = BindingInterface->GetBindingKey(EInputActionType::EIAT_Interact);

								if (InteractionKey.IsValid())
									InteractionKeyText = InteractionKey.GetDisplayName();
							}

					WidgetsManager->SetInteractionWidgetData(EWidgetId::EWI_InteractionHint, FInteractionTargetingData {.TargetName = InteractionData.Name, .TargetInteractionText = InteractionData.InteractionText, .InteractionKeyText = InteractionKeyText});
					WidgetsManager->ShowWidget(EWidgetId::EWI_InteractionHint); // hint shows up
					WidgetsManager->SetInteractionWidgetData(EWidgetId::EWI_Reticle, FInteractionTargetingData{ .WidgetColorType = EWidgetColorType::EWCT_Targeting });
				}
			}

			else
			{
				if (WidgetsManager)
				{
					WidgetsManager->HideWidget(EWidgetId::EWI_InteractionHint); // hint hides
					WidgetsManager->SetInteractionWidgetData(EWidgetId::EWI_Reticle, FInteractionTargetingData{ .WidgetColorType = EWidgetColorType::EWCT_Default });
				}
			}

			LastInteractionTarget = HitActor;
		}
	}

	else
	{
		if (LastInteractionTarget)
		{
			if (WidgetsManager)
			{
				WidgetsManager->HideWidget(EWidgetId::EWI_InteractionHint); // hint hides
				WidgetsManager->SetInteractionWidgetData(EWidgetId::EWI_Reticle, FInteractionTargetingData{ .WidgetColorType = EWidgetColorType::EWCT_Default });
			}

			LastInteractionTarget = nullptr;
		}
	}
}

void UCharacterInteractionComponent::OnInteract()
{
	if (LastInteractionTarget)
		if (auto InteractionInterface = Cast<IInteractionInterface>(LastInteractionTarget))
			InteractionInterface->Interact(OwnerCharacter);
}