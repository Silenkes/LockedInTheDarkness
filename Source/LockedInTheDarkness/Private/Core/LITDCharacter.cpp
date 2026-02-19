#include "Core/LITDCharacter.h"
#include "InputActionValue.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "CustomComponents/CharacterInteractionComponent.h"

ALITDCharacter::ALITDCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	GetCapsuleComponent()->InitCapsuleSize(55.f, 96.f);
	
	ViewCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("ViewCamera"));
	ViewCamera->SetupAttachment(GetCapsuleComponent());
	ViewCamera->SetRelativeLocation(FVector(-10.f, 0.f, 60.f));
	ViewCamera->bUsePawnControlRotation = true;

	InteractionComponent = CreateDefaultSubobject<UCharacterInteractionComponent>(TEXT("InteractionComponent"));
}

void ALITDCharacter::BeginPlay()
{
	Super::BeginPlay();

	InteractionComponent->Initialize(ViewCamera);
}

void ALITDCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ALITDCharacter::Jump()
{
	Super::Jump();
}

void ALITDCharacter::Move(const FInputActionValue& Value)
{
	const FVector2D MovementVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		AddMovementInput(GetActorForwardVector(), MovementVector.Y);
		AddMovementInput(GetActorRightVector(), MovementVector.X);
	}
}

void ALITDCharacter::Look(const FInputActionValue& Value)
{
	FVector2D LookAxisVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		AddControllerPitchInput(LookAxisVector.Y * CameraSensitivityMultiplier);
		AddControllerYawInput(LookAxisVector.X * CameraSensitivityMultiplier);
	}
}

void ALITDCharacter::OnCrouch()
{
	Crouch();
}

void ALITDCharacter::OnUnCrouch()
{
	UnCrouch();
}

void ALITDCharacter::Interact()
{
	InteractionComponent->OnInteract();
}