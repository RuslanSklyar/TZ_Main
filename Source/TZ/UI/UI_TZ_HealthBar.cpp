#include "UI/UI_TZ_HealthBar.h"

#include "CoreMinimal.h"
#include "Components/CanvasPanelSlot.h"

// --------------------------------------------------------------------------------
void UUI_TZ_HealthBar::SetHealthPercent(float Value)
{
    if (HealthProgressBar)
    {
        HealthProgressBar->SetPercent(Value);
    }
}

// --------------------------------------------------------------------------------
void UUI_TZ_HealthBar::SetDefaultPosition()
{
	if (HealthProgressBar)
	{
		if (UCanvasPanelSlot* CanvasSlot = Cast<UCanvasPanelSlot>(HealthProgressBar->Slot))
		{
			CanvasSlot->SetAnchors(FAnchors(0.5f, 0.5f));
			CanvasSlot->SetAlignment(FVector2D(0.5f, 0.5f));
			CanvasSlot->SetPosition(FVector2D(0.f, 0.f));

			CanvasSlot->SetSize(FVector2D(100.f, 10.f));
		}
	}
}