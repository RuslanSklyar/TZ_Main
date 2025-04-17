#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TZ_BasePickUpActor.generated.h"

// --------------------------------------------------------------------------------
UCLASS()
class TZ_API ATZ_BasePickUpActor : public AActor
{
	GENERATED_BODY()
	
public:	
	ATZ_BasePickUpActor();

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

public:
// --------------------------------------------------------------------------------
// Variables
	UPROPERTY(VisibleAnywhere, Category = "Pickup|Components")
	class UStaticMeshComponent* MeshComponent;

	UPROPERTY(VisibleAnywhere, Category = "Pickup|Components")
	class USphereComponent* SphereComponent;

	UPROPERTY(VisibleAnywhere, Category = "Pickup|Components")
	class UTextRenderComponent* TextComponent;

// Methods
protected:
	UFUNCTION()
	virtual void OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
};
