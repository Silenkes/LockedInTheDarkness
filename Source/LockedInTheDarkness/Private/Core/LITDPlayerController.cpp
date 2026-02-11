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
				EnhancedInputComponent->BindAction(CrouchAction, ETriggerEvent::Started, ControlledCharacter, &ALITDCharacter::CrouchPressed);
				EnhancedInputComponent->BindAction(CrouchAction, ETriggerEvent::Completed, ControlledCharacter, &ALITDCharacter::CrouchReleased);
			}
		}

		else
		{
			UE_LOG(LogTemp, Error, TEXT("ControlledCharacter is null during SetupInputComponent!"));
		}
	}
}