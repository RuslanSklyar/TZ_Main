#include "AC_Heath.h"

// --------------------------------------------------------------------------------
UAC_Heath::UAC_Heath()
{
	PrimaryComponentTick.bCanEverTick = true;

// Initialization default variables
	SetHealthMax(100.f);
	SetHealth(GetHealthMax());
}


// --------------------------------------------------------------------------------
// Event Begin Play
void UAC_Heath::BeginPlay()
{
	Super::BeginPlay();
}


// --------------------------------------------------------------------------------
// Event Tick
void UAC_Heath::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

// --------------------------------------------------------------------------------
// Event Take Damage
void UAC_Heath::TakeDamage(float Value)
{
	CalcHealth(Value);
}

// --------------------------------------------------------------------------------
// Event Append Health
void UAC_Heath::TakeHealth(float Value)
{
	CalcHealth(Value);
}

// --------------------------------------------------------------------------------
// Getter Health
float UAC_Heath::GetHealth()
{
	return Health;
}

// --------------------------------------------------------------------------------
// Setter Health
void UAC_Heath::SetHealth(float Value)
{
	Health = Value;
}

// --------------------------------------------------------------------------------
// Getter Max Health
float UAC_Heath::GetHealthMax()
{
	return HealthMax;
}

// --------------------------------------------------------------------------------
// Setter Max Health
void UAC_Heath::SetHealthMax(float Value)
{
	HealthMax = Value;
}

// --------------------------------------------------------------------------------
// Calculated Health
void UAC_Heath::CalcHealth(float Value)
{
	float CurrentHealth = GetHealth();
	float BufferHealth = CurrentHealth + Value;
	SetHealth(BufferHealth);

	if (BufferHealth <= 0)
	{
		Death();
	}

	UpdateWidget();
}

// --------------------------------------------------------------------------------
// Event Death
void UAC_Heath::Death()
{
	if (GetOwner()->GetClass()->ImplementsInterface(UI_Death::StaticClass()))
	{
		II_Death* Interface = Cast<II_Death>(GetOwner());

		if (Interface)
		{
			Interface->Death();
		}
	}
}

// --------------------------------------------------------------------------------
// Set pointer Health Widget
void UAC_Heath::SetWidget(UUI_TZ_HealthBar* Widget)
{
	WidgetBar = Widget;
	UpdateWidget();
}

// --------------------------------------------------------------------------------
// Update Health Widget
void UAC_Heath::UpdateWidget()
{
	float HealthPercent = FMath::Clamp(GetHealth() / GetHealthMax(), 0.f, 1.f);
	WidgetBar->SetHealthPercent(HealthPercent);
}
