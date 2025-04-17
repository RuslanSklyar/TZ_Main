#pragma once

#include "CoreMinimal.h"

#include "Components/ActorComponent.h"
#include "I_Death.h"
#include "UI/UI_TZ_HealthBar.h"

#include "AC_Heath.generated.h"

// --------------------------------------------------------------------------------
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TZ_API UAC_Heath : public UActorComponent
{
	GENERATED_BODY()

public:	
	UAC_Heath();

protected:
	virtual void BeginPlay() override;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
// --------------------------------------------------------------------------------
// Variables
	UPROPERTY()
	float Health;

	UPROPERTY()
	float HealthMax;

	//UI
	UPROPERTY()
	UUI_TZ_HealthBar* WidgetBar;

// --------------------------------------------------------------------------------
// Methods
public:
	UFUNCTION(BlueprintCallable, Category = "Health|Event Called Logic")
	void TakeDamage(float Value);
	UFUNCTION(BlueprintCallable, Category = "Health|Event Called Logic")
	void TakeHealth(float Value);

// Getters - Setters
	UFUNCTION(BlueprintCallable, Category = "Health|Getters")
	float GetHealth();
	UFUNCTION(BlueprintCallable, Category = "Health|Setters")
	void SetHealth(float Value);

	UFUNCTION(BlueprintCallable, Category = "Health|Getters")
	float GetHealthMax();
	UFUNCTION(BlueprintCallable, Category = "Health|Setters")
	void SetHealthMax(float Value);

// Pawn States
	UFUNCTION()
	void CalcHealth(float Value);

	UFUNCTION()
	void Death();

// UI
	UFUNCTION(BlueprintCallable, Category = "Health|UI")
	void SetWidget(UUI_TZ_HealthBar* Widget);

	UFUNCTION(BlueprintCallable, Category = "Health|UI")
	void UpdateWidget();
};
