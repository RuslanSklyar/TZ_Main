#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"

#include "GameFramework/FloatingPawnMovement.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/InputComponent.h"
#include "I_Death.h"
#include "UI/UI_TZ_HealthBar.h"

#include "ZT_Dron.generated.h"
// --------------------------------------------------------------------------------
UCLASS()
class TZ_API AZT_Dron : public APawn, public II_Death
{
	GENERATED_BODY()

public:
	AZT_Dron();

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

// Movement
	// Mouse
	void Turn(float Value);
	void LookUp(float Value);

	//Keyboard
	void MoveForvard(float Value);
	void MoveRight(float Value);
	void Flying(float Value);

	//Weapon
	void StartFire();
	void StartAiming();
	void StopAiming();

public:
// --------------------------------------------------------------------------------
// Variables
	// Mesh
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Dron|Component")
	class UStaticMeshComponent* Body;

	// Camera
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Dron|Component")
	USpringArmComponent* CameraBoom;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Dron|Component")
	UCameraComponent* CameraThirdPerson;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Dron|Component")
	UCameraComponent* CameraFirstPerson;

	// Movement
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Dron|Movement")
	UFloatingPawnMovement* FloatingMovement;

	// Weapon
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Dron|Weapon")
	float fDronDamage;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Dron|Weapon")
	int32 Ammo;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Dron|Weapon")
	bool bIsAiming;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Dron|Weapon")
	TSubclassOf<class ATZ_Bullet> BulletClass;

	// Health Component
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Dron|HealthComponent")
	class UAC_Heath* HealthComponent;

	// Pawn State
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Dron|PawnState")
	bool bIsDead;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Dron|UI")
	TSubclassOf<UUI_TZ_HealthBar> WidgetClass;

public:
// --------------------------------------------------------------------------------
// Methods
	// Weapon
	UFUNCTION(BlueprintCallable, Category = "Dron|Weapon")
	void SetAmmo(int32 Value);

	// Interface override
	virtual void Death() override;
	virtual bool GetIsDead() override;


};
