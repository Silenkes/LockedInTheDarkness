#include "UI/ReticleWidget.h"
#include "Components/Image.h"

void UReticleWidget::NativePreConstruct()
{
	Super::NativePreConstruct();

	if (ImageReticle)
		ImageReticle->SetColorAndOpacity(ReticleDefaultColor);
}

void UReticleWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if (ImageReticle)
		ImageReticle->SetColorAndOpacity(ReticleDefaultColor);
}

void UReticleWidget::OnTargeted(const FInteractionTargetingData& TargetingData)
{
	if (ImageReticle)
		switch (TargetingData.WidgetColorType)
		{
		case EWidgetColorType::EWCT_Default:
			ImageReticle->SetColorAndOpacity(ReticleDefaultColor);
			break;

		case EWidgetColorType::EWCT_Targeting:
			ImageReticle->SetColorAndOpacity(ReticleTargetingColor);
			break;

		default:
			break;
		}
}