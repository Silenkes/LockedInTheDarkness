#include "Core/LITDPlayerController.h"
#include "Core/LITDCharacter.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"

void ALITDPlayerController::BeginPlay()
{
	Super::BeginPlay();

	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
		if(InputMappingContext)
			Subsystem->AddMappingContext(InputMappingContext, 0);
}

void ALITDPlayerController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	ControlledCharacter = Cast<ALITDCharacter>(InPawn);

	if (ControlledCharacter)
	{
		UE_LOG(LogTemp, Warning, TEXT("PlayerController possessed %s"), *ControlledCharacter->GetName());
	}

	else
	{
		UE_LOG(LogTemp, Error, TEXT("PlayerController possessed a Pawn that is not ALITDCharacter!"));
	}

	BindEnhancedInputComponent();
}

FKey ALITDPlayerController::GetBindingKey(EInputActionType ActionType) const
{
	UInputAction* Action = nullptr;

	switch (ActionType)
	{
	case EInputActionType::EIAT_Move:
		Action = MoveAction;
		break;

	case EInputActionType::EIAT_Look:
		Action = LookAction;
		break;

	case EInputActionType::EIAT_Jump:
		Action = JumpAction;
		break;

	case EInputActionType::EIAT_Crouch:
		Action = CrouchAction;
		break;

	case EInputActionType::EIAT_Interact:
		Action = InteractAction;
		break;

	default:
		break;
	}

	if (!Action)
		return EKeys::Invalid;

	const ULocalPlayer* LocalPlayer = GetLocalPlayer();

	if (!LocalPlayer)
		return EKeys::Invalid;

	const UEnhancedInputLocalPlayerSubsystem* Subsystem = LocalPlayer->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>();

	if (!Subsystem)
		return EKeys::Invalid;

	const TArray<FKey> Keys = Subsystem->QueryKeysMappedToAction(Action);

	for (const FKey& Key : Keys)
	{
		if (Key.IsValid())
		{
			return Key;
		}
	}

	return EKeys::Invalid;
}

void ALITDPlayerController::BindEnhancedInputComponent()
{
	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(InputComponent))
	{
		if (ControlledCharacter)
		{
			if (MoveAction)
				EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, ControlledCharacter, &ALITDCharacter::Move);

			if (LookAction)
				EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, ControlledCharacter, &ALITDCharacter::Look);

			if (JumpAction)
				EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Triggered, ControlledCharacter, &ALITDCharacter::Jump);

			if (CrouchAction)
			{
				EnhancedInputComponent->BindAction(CrouchAction, ETriggerEvent::Started, ControlledCharacter, &ALITDCharacter::OnCrouch);
				EnhancedInputComponent->BindAction(CrouchAction, ETriggerEvent::Completed, ControlledCharacter, &ALITDCharacter::OnUnCrouch);
			}

			if (InteractAction)
				EnhancedInputComponent->BindAction(InteractAction, ETriggerEvent::Started, ControlledCharacter, &ALITDCharacter::Interact);
		}

		else
		{
			UE_LOG(LogTemp, Error, TEXT("ControlledCharacter is null during SetupInputComponent!"));
		}
	}
}