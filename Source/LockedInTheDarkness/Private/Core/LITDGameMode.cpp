#include "Core/LITDGameMode.h"
#include "Core/LITDHUD.h"
#include "Kismet/GameplayStatics.h"

void ALITDGameMode::BeginPlay()
{
	Super::BeginPlay();
	
	APlayerController* PlayerController = UGameplayStatics::GetPlayerController(this, 0);
	ALITDHUD* WidgetsManager = Cast<ALITDHUD>(PlayerController->GetHUD());
	
	PlayerController->SetShowMouseCursor(false);
	PlayerController->SetInputMode(FInputModeGameOnly());

	if (WidgetsManager)
	{
		WidgetsManager->AddWidget(EWidgetId::EWI_Reticle);
	}
}
