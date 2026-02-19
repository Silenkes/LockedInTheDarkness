#include "UI/InteractionHintWidget.h"
#include "Components/TextBlock.h"

void UInteractionHintWidget::OnTargeted(const FInteractionTargetingData& TargetingData)
{
	if (TextObjectName)
		TextObjectName->SetText(TargetingData.TargetName);

	if (TextInteraction)
		TextInteraction->SetText(TargetingData.TargetInteractionText);

	if (TextInteractionKey)
		TextInteractionKey->SetText(TargetingData.InteractionKeyText);
}