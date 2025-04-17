#include "PickUpActor/PickupHealth/TZ_PickupHealth.h"
#include "AC_Heath.h"


// --------------------------------------------------------------------------------
ATZ_PickupHealth::ATZ_PickupHealth()
{
	Health = 25.f;
}

// --------------------------------------------------------------------------------
void ATZ_PickupHealth::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	Super::OnOverlapBegin(OverlappedComponent, OtherActor, OtherComp, OtherBodyIndex, bFromSweep, SweepResult);

	UAC_Heath* Component = OtherActor->GetComponentByClass<UAC_Heath>();
	if (Component)
	{
		if (Component->GetHealth() < Component->GetHealthMax())
		{
			Component->TakeHealth(Health);
			Destroy();
		}
	}
}