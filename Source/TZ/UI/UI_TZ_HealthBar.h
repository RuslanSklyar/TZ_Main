#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/CanvasPanelSlot.h"
#include "Components/ProgressBar.h"

#include "UI_TZ_HealthBar.generated.h"

// --------------------------------------------------------------------------------
UCLASS()
class TZ_API UUI_TZ_HealthBar : public UUserWidget
{
	GENERATED_BODY()
	
public:

// --------------------------------------------------------------------------------
// Variables
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UProgressBar* HealthProgressBar;

// Methods
	UFUNCTION(BlueprintCallable, Category = "HealthBar|Progressbar")
	void SetHealthPercent(float Value);

	UFUNCTION(BlueprintCallable, Category = "HealthBar|Progressbar")
	void SetDefaultPosition();
};