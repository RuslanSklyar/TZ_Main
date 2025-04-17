#include "Dron/ZT_Dron.h"
#include "TZ_Bullet.h"
#include "AC_Heath.h"

// --------------------------------------------------------------------------------
AZT_Dron::AZT_Dron()
{
	PrimaryActorTick.bCanEverTick = true;

	// Create mesh
	Body = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Body"));
	RootComponent = Body;

	// Create Spring Arm
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 300.f;
	CameraBoom->bUsePawnControlRotation = true;

	// Create Camera
	CameraThirdPerson = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraThirdPerson"));
	CameraThirdPerson->SetupAttachment(CameraBoom);
	CameraThirdPerson->bUsePawnControlRotation = true;

	CameraFirstPerson = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraFirstPerson"));
	CameraFirstPerson->SetupAttachment(RootComponent);
	CameraFirstPerson->Activate(false);

	// Create movement component
	FloatingMovement = CreateDefaultSubobject<UFloatingPawnMovement>(TEXT("FloatingPawnMovement"));

	// Create health component
	HealthComponent = CreateDefaultSubobject<UAC_Heath>(TEXT("AC_HealthComponent"));

// Initialization default variables
	// Weapon
	bIsAiming = false;
	fDronDamage = -25.f;
	Ammo = 10;

	// State pawn
	bIsDead = false;

}
// --------------------------------------------------------------------------------
// Event Begin Play
void AZT_Dron::BeginPlay()
{
	Super::BeginPlay();

	if (WidgetClass)
	{
		UUI_TZ_HealthBar* Widget = CreateWidget<UUI_TZ_HealthBar>(GetWorld(), WidgetClass);
		if (Widget)
		{
			Widget->AddToViewport();
			HealthComponent->SetWidget(Widget);
		}
	}
}

// --------------------------------------------------------------------------------
// Event Tick
void AZT_Dron::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if(!bIsDead)
		SetActorRotation(GetControlRotation());

}

// --------------------------------------------------------------------------------
// Setup Player Input Component
void AZT_Dron::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("Turn", this, &AZT_Dron::Turn);
	PlayerInputComponent->BindAxis("LookUp", this, &AZT_Dron::LookUp);

	PlayerInputComponent->BindAxis("MoveForvard", this, &AZT_Dron::MoveForvard);
	PlayerInputComponent->BindAxis("MoveRight", this, &AZT_Dron::MoveRight);
	PlayerInputComponent->BindAxis("Fly", this, &AZT_Dron::Flying);

	PlayerInputComponent->BindAction("Fire", IE_Pressed, this, &AZT_Dron::StartFire);

	PlayerInputComponent->BindAction("Aiming", IE_Pressed, this, &AZT_Dron::StartAiming);
	PlayerInputComponent->BindAction("Aiming", IE_Released, this, &AZT_Dron::StopAiming);
}

// --------------------------------------------------------------------------------
// Mouse Turn
void AZT_Dron::Turn(float Value)
{
	if (bIsDead) return;
	AddControllerYawInput(Value);
}

// --------------------------------------------------------------------------------
// Mouse LookUp
void AZT_Dron::LookUp(float Value)
{
	if (bIsDead) return;
	AddControllerPitchInput(Value);
}

// --------------------------------------------------------------------------------
// Movement WS
void AZT_Dron::MoveForvard(float Value)
{
	if (Value == 0.f) return;

	FRotator ControlRotation = Controller->GetControlRotation();
	ControlRotation.Pitch = 0.0f;
	ControlRotation.Roll = 0.0f;

	FVector Forward = FRotationMatrix(ControlRotation).GetUnitAxis(EAxis::X);
	AddMovementInput(Forward, Value);
}

// --------------------------------------------------------------------------------
// Movement AD
void AZT_Dron::MoveRight(float Value)
{
	if (Value == 0.f) return;

	FRotator ControlRotation = Controller->GetControlRotation();
	ControlRotation.Pitch = 0.0f;
	ControlRotation.Roll = 0.0f;

	FVector Right = FRotationMatrix(ControlRotation).GetUnitAxis(EAxis::Y);
	AddMovementInput(Right, Value);
}

// --------------------------------------------------------------------------------
// Movement Fly
void AZT_Dron::Flying(float Value)
{
	if (Value == 0.f || bIsDead) return;

	AddMovementInput(FVector(0.f, 0.f, 1.f), Value);
}

// --------------------------------------------------------------------------------
// Weapon - Fire
void AZT_Dron::StartFire()
{
	if (bIsDead || !bIsAiming || !BulletClass || Ammo <= 0) return;

	FActorSpawnParameters SpawnParams;
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	FVector MuzzleLocation = GetActorLocation() + GetActorForwardVector() * 100.f;
	FRotator MuzzleRotation = GetControlRotation();

	ATZ_Bullet* Bullet = GetWorld()->SpawnActor<ATZ_Bullet>(BulletClass, MuzzleLocation, MuzzleRotation, SpawnParams);
	Bullet->SetBulletDamage(fDronDamage);

	Ammo--;
}

// --------------------------------------------------------------------------------
// Weapon - Aiming Start
void AZT_Dron::StartAiming()
{
	if (bIsDead) return;
	bIsAiming = true;
	CameraThirdPerson->SetActive(false);
	CameraFirstPerson->SetActive(true);
}

// --------------------------------------------------------------------------------
// Weapon - Aiming End
void AZT_Dron::StopAiming()
{
	if (bIsDead) return;
	bIsAiming = false;
	CameraThirdPerson->SetActive(true);
	CameraFirstPerson->SetActive(false);
}

// --------------------------------------------------------------------------------
// Weapon - Add Ammo
void AZT_Dron::SetAmmo(int32 Value)
{
	Ammo += Value;
}

// --------------------------------------------------------------------------------
// Event Death
void AZT_Dron::Death()
{
	bIsDead = true;
	FloatingMovement->Deactivate();
	Body->SetSimulatePhysics(true);

	Body->SetEnableGravity(true);
	CameraThirdPerson->SetActive(true);
	CameraFirstPerson->SetActive(false);
}

// --------------------------------------------------------------------------------
// Interface - Get Death Pawn State
bool AZT_Dron::GetIsDead()
{
	return bIsDead;
}
