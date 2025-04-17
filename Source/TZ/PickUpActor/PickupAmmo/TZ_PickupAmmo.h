#pragma once

#include "CoreMinimal.h"
#include "PickUpActor/TZ_BasePickUpActor.h"
#include "TZ_PickupAmmo.generated.h"

// --------------------------------------------------------------------------------
UCLASS()
class TZ_API ATZ_PickupAmmo : public ATZ_BasePickUpActor
{
	GENERATED_BODY()

public:

	ATZ_PickupAmmo();

protected:
// --------------------------------------------------------------------------------
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Pickup|Ammo")
	int32 Ammo;

protected:
	virtual void OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) override;
	
};
