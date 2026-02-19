// * This is the widgets manager class

#include "Core/LITDHUD.h"
#include "Blueprint/UserWidget.h"
#include "Interfaces/InteractionTargetingInterface.h"

UUserWidget* ALITDHUD::AddWidget(EWidgetId WidgetId)
{
	if (CreatedWidgets.Contains(WidgetId))
		return CreatedWidgets[WidgetId];

	TSubclassOf<UUserWidget>* WidgetClass = WidgetClasses.Find(WidgetId);

	if (WidgetClass && WidgetClass->Get())
	{
		UUserWidget* Widget = CreateWidget<UUserWidget>(GetWorld(), *WidgetClass);
		Widget->AddToViewport();
		LastCreatedWidget = Widget;
		CreatedWidgets.Add(WidgetId, Widget);

		return Widget;
	}

	return nullptr;
}

void ALITDHUD::ShowWidget(EWidgetId WidgetId)
{
	if (!CreatedWidgets.Contains(WidgetId))
		AddWidget(WidgetId);

	if (UUserWidget** Widget = CreatedWidgets.Find(WidgetId))
	{
		if (IsValid(*Widget))
			if (!(*Widget)->IsVisible())
				((*Widget)->SetVisibility(ESlateVisibility::Visible));
	}
}

void ALITDHUD::HideWidget(EWidgetId WidgetId)
{
	if (UUserWidget** Widget = CreatedWidgets.Find(WidgetId))
	{
		if (IsValid(*Widget))
			if ((*Widget)->IsVisible())
				(*Widget)->SetVisibility(ESlateVisibility::Hidden);
	}
}

void ALITDHUD::SetInteractionWidgetData(EWidgetId WidgetId, const FInteractionTargetingData& Data)
{
	if (UUserWidget** Widget = CreatedWidgets.Find(WidgetId))
	{
		if (IsValid(*Widget))
		{
			if (IInteractionTargetingInterface* InteractionTargetingInterface = Cast<IInteractionTargetingInterface>(*Widget))
				InteractionTargetingInterface->OnTargeted(Data);
		}
	}
}

void ALITDHUD::RemoveWidget(EWidgetId WidgetId)
{
	if (UUserWidget** Widget = CreatedWidgets.Find(WidgetId))
	{
		if (IsValid(*Widget))
			(*Widget)->RemoveFromParent();

		CreatedWidgets.Remove(WidgetId);
	}
}

void ALITDHUD::RemoveLastWidget()
{
	if (IsValid(LastCreatedWidget))
	{
		LastCreatedWidget->RemoveFromParent();
		LastCreatedWidget = nullptr;
	}
}
