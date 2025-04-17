#include "PickUpActor/PickupAmmo/TZ_PickupAmmo.h"
#include "Dron/ZT_Dron.h"

// --------------------------------------------------------------------------------
ATZ_PickupAmmo::ATZ_PickupAmmo()
{
	Ammo = 1;
}

// --------------------------------------------------------------------------------
// Collision Overlap
void ATZ_PickupAmmo::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	Super::OnOverlapBegin(OverlappedComponent, OtherActor, OtherComp, OtherBodyIndex, bFromSweep, SweepResult);
	AZT_Dron* Player = Cast<AZT_Dron>(OtherActor);

	if (Player)
	{
		Player->SetAmmo(Ammo);
	}
	Destroy();
}