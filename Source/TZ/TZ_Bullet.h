#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TZ_Bullet.generated.h"

// --------------------------------------------------------------------------------
UCLASS()
class TZ_API ATZ_Bullet : public AActor
{
	GENERATED_BODY()
	
public:	
	ATZ_Bullet();

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

public:
// --------------------------------------------------------------------------------
// Variables

	// Mesh
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Bullet|Components")
	class UStaticMeshComponent* BulletMesh;

	// Collision
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Bullet|Components")
	class USphereComponent* CollisionComponent;

	// Movement
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Bullet|Movement")
	class UProjectileMovementComponent* ProjectileMovement;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Bullet|Audio")
	USoundBase* FireSound;

private:
	// Weapon
	UPROPERTY()
	float Damage;

public:
// Methods

	// Event Hit
	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	// Weapon - Setter Damage
	UFUNCTION()
	void SetBulletDamage(float Value);
};
