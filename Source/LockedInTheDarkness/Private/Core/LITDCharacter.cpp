#include "Core/LITDCharacter.h"
#include "InputActionValue.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Interfaces/InteractionInterface.h"


ALITDCharacter::ALITDCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	GetCapsuleComponent()->InitCapsuleSize(55.f, 96.f);
	
	ViewCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("ViewCamera"));
	ViewCamera->SetupAttachment(GetCapsuleComponent());
	ViewCamera->SetRelativeLocation(FVector(-10.f, 0.f, 60.f));
	ViewCamera->bUsePawnControlRotation = true;
}

void ALITDCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	if (UCapsuleComponent* Capsule = GetCapsuleComponent())
	{
		Capsule->OnComponentBeginOverlap.AddDynamic(this, &ALITDCharacter::OnCapsuleBeginOverlap);
		Capsule->OnComponentEndOverlap.AddDynamic(this, &ALITDCharacter::OnCapsuleEndOverlap);
	}
}

void ALITDCharacter::OnCapsuleBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (auto InteractionInterface = Cast<IInteractionInterface>(OtherActor))
	{
		UE_LOG(LogTemp, Display, TEXT("[%s] Begin overlap with %s via interface!"), *GetName(), *OtherActor->GetName());
		InteractionInterface->Interact(this);
	}
}

void ALITDCharacter::OnCapsuleEndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (auto InteractionInterface = Cast<IInteractionInterface>(OtherActor))
		InteractionInterface->EndInteract(this);
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

void ALITDCharacter::CrouchPressed()
{
	Crouch();
}

void ALITDCharacter::CrouchReleased()
{
	UnCrouch();
}
