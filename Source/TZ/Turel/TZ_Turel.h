#pragma once

#include "CoreMinimal.h"

#include "GameFramework/Pawn.h"
#include "I_Death.h"
#include "UI/UI_TZ_HealthBar.h"

#include "TZ_Turel.generated.h"

// --------------------------------------------------------------------------------
UCLASS()
class TZ_API ATZ_Turel : public APawn, public II_Death
{
	GENERATED_BODY()

public:
	ATZ_Turel();

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

public:
// --------------------------------------------------------------------------------
// Variables
	// Mesh
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Turel|Components")
	class UStaticMeshComponent* Head;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Turel|Components")
	class UStaticMeshComponent* Stand;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Turel|Components")
	class UStaticMeshComponent* Body;

	// Weapon
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Turel|Weapon")
	USceneComponent* Muzzle;
	
	// Collision Can See Player
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Turel|Components")
	class USphereComponent* CollisionComponent;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Turel|Perception")
	float fSphereRadius;

private:
	UPROPERTY()
	bool bIsSeePlayer;
	UPROPERTY()
	AActor* TargetPawn;

	// Weapon
	UPROPERTY()
	bool bIsFire;

	UPROPERTY()
	FTimerHandle FireTimerHandle;

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Turel|Weapon")
	float fTurelDamage;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Turel|Weapon")
	float fFireRate;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Turel|Weapon")
	TSubclassOf<class ATZ_Bullet> BulletClass;

	// UI
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Turel|UI")
	class UWidgetComponent* HealthBarWidgetComponent;
	UPROPERTY()
	class UUI_TZ_HealthBar* HealthBarWidget;

	// Health component
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class UAC_Heath* HealthComponent;

	// Pawn State
	UPROPERTY()
	bool bIsDead;

// --------------------------------------------------------------------------------
// Methods
	// Interface override
	virtual void Death() override;
	virtual bool GetIsDead() override;

	// UI
	UFUNCTION(BlueprintCallable, Category = "Turel|UI")
	void UpdateWidget();

	// Weapon Events
	UFUNCTION(BlueprintCallable, Category = "Turel|WeaponEvents")
	void EventFire();
	UFUNCTION(BlueprintCallable, Category = "Turel|WeaponEvents")
	void ResetFire();

	// Collision Can See Radiuse
	UFUNCTION(BlueprintCallable, Category = "Turel|Perception")
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
		const FHitResult& SweepResult);

	UFUNCTION(BlueprintCallable, Category = "Turel|Perception")
	void OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
};
