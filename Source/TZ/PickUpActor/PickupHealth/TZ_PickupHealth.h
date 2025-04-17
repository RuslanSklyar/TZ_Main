#pragma once

#include "CoreMinimal.h"
#include "PickUpActor/TZ_BasePickUpActor.h"
#include "TZ_PickupHealth.generated.h"

// --------------------------------------------------------------------------------
UCLASS()
class TZ_API ATZ_PickupHealth : public ATZ_BasePickUpActor
{
	GENERATED_BODY()
	
public:

	ATZ_PickupHealth();

protected:
// --------------------------------------------------------------------------------
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Pickup|Health")
	float Health;

	virtual void OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
		bool bFromSweep, const FHitResult& SweepResult) override;
};
