#include "Turel/TZ_Turel.h"

#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Components/WidgetComponent.h"
#include "UI/UI_TZ_HealthBar.h"
#include "TZ_Bullet.h"
#include "AC_Heath.h"

// --------------------------------------------------------------------------------
ATZ_Turel::ATZ_Turel()
{
	PrimaryActorTick.bCanEverTick = true;

	// Create Mesh
	Stand = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("TurelStand"));
	RootComponent = Stand;

	Body = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("TurelBody"));
	Body->SetupAttachment(Stand);

	Head = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("TurelHead"));
	Head->SetupAttachment(Body);

	// Create Weapon Muzzle poin
	Muzzle = CreateDefaultSubobject<USceneComponent>(TEXT("Muzzle"));
	Muzzle->SetupAttachment(Head);

	// Create Collision Perception
	CollisionComponent = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComponent"));
	CollisionComponent->SetupAttachment(Head);
	CollisionComponent->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);

	// Create Collision CallBack
	CollisionComponent->OnComponentBeginOverlap.AddDynamic(this, &ATZ_Turel::OnOverlapBegin);
	CollisionComponent->OnComponentEndOverlap.AddDynamic(this, &ATZ_Turel::OnOverlapEnd);

	// Create HealthBar Widget
	HealthBarWidgetComponent = CreateDefaultSubobject<UWidgetComponent>(TEXT("HealthBarWidgetComponent"));
	HealthBarWidgetComponent->SetupAttachment(RootComponent);
	HealthBarWidgetComponent->SetWidgetClass(UUI_TZ_HealthBar::StaticClass());
	HealthBarWidgetComponent->SetDrawSize(FVector2D(100.f, 20.f));
	HealthBarWidgetComponent->SetVisibility(true);
	HealthBarWidgetComponent->SetWidgetSpace(EWidgetSpace::Screen);

	// Create Health Component
	HealthComponent = CreateDefaultSubobject<UAC_Heath>(TEXT("AC_HealthComponent"));

// Initialization default variables
	bIsDead = false;

	// Weapon
	bIsFire = false;
	fTurelDamage = -10.f;
	fFireRate = 1.f;

	// Perception
	bIsSeePlayer = false;
	fSphereRadius = 500.f;

	CollisionComponent->SetSphereRadius(fSphereRadius);
}

// --------------------------------------------------------------------------------
// Event BeginPlay
void ATZ_Turel::BeginPlay()
{
	Super::BeginPlay();

	FVector ActorLocation = GetActorLocation();
	FVector WidgetLocation = ActorLocation + FVector(0.f, 0.f, 200.f);

	HealthBarWidgetComponent->SetWorldLocation(WidgetLocation);

	if (!HealthBarWidget)
	{
		HealthBarWidget = Cast<UUI_TZ_HealthBar>(HealthBarWidgetComponent->GetUserWidgetObject());
		HealthComponent->SetWidget(HealthBarWidget);
		HealthBarWidget->SetDefaultPosition();
	}

}

// --------------------------------------------------------------------------------
// Event Tick
void ATZ_Turel::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!bIsDead)
	{

		if (bIsSeePlayer)
		{
			FRotator TargetRotation = (TargetPawn->GetActorLocation() - GetActorLocation()).Rotation();

			FRotator BodyRotation = FRotator(0.f, TargetRotation.Yaw, 0.f);

			Body->SetWorldRotation(BodyRotation);
			Head->SetWorldRotation(TargetRotation);

			if (!bIsFire)
			{
				EventFire();
			}
		}
	}
}

// --------------------------------------------------------------------------------
// Setup Player Input Component
void ATZ_Turel::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}


// --------------------------------------------------------------------------------
// Weapon Event Fire
void ATZ_Turel::EventFire()
{
	if (!BulletClass || !TargetPawn) return;

	// Check Target State - IsDead?
	if (TargetPawn->GetClass()->ImplementsInterface(UI_Death::StaticClass()))
	{
		II_Death* Interface = Cast<II_Death>(TargetPawn);

		if (Interface)
		{
			if (Interface->GetIsDead())
			{
				bIsSeePlayer = false;
				TargetPawn = nullptr;
				return;
			}
		}
	}

	// Event Fire
	bIsFire = true;
	GetWorldTimerManager().ClearTimer(FireTimerHandle);

	FVector MuzzleLocation = Muzzle->GetComponentLocation();
	FRotator MuzzleRotation = (TargetPawn->GetActorLocation() - MuzzleLocation).Rotation();

	FActorSpawnParameters SpawnParams;
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	ATZ_Bullet* Bullet = GetWorld()->SpawnActor<ATZ_Bullet>(BulletClass, MuzzleLocation, MuzzleRotation, SpawnParams);
	Bullet->SetBulletDamage(fTurelDamage);

	GetWorldTimerManager().SetTimer(FireTimerHandle, this, &ATZ_Turel::ResetFire, fFireRate, false);
}

// --------------------------------------------------------------------------------
// Weapon End Delay Fire
void ATZ_Turel::ResetFire()
{
	bIsFire = false;
}

// --------------------------------------------------------------------------------
// Interface override - Set Death Pawn State
void ATZ_Turel::Death()
{
	bIsDead = true;
	CollisionComponent->DestroyComponent();
}

// --------------------------------------------------------------------------------
// Interface override - Get Death Pawn State
bool ATZ_Turel::GetIsDead()
{
	return bIsDead;
}

// --------------------------------------------------------------------------------
// UI - Update Widget
void ATZ_Turel::UpdateWidget()
{
	float HealthPercent = FMath::Clamp(HealthComponent->GetHealth() / HealthComponent->GetHealthMax(), 0.f, 1.f);
	HealthBarWidget->SetHealthPercent(HealthPercent);
}

// --------------------------------------------------------------------------------
// Collision CallBack - Begin Overlap
void ATZ_Turel::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor && OtherActor != this && OtherActor->GetClass() != GetClass())
	{
		TargetPawn = OtherActor;
		bIsSeePlayer = true;
	}
}

// --------------------------------------------------------------------------------
// Collision CallBack - End Overlap
void ATZ_Turel::OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (OtherActor == TargetPawn)
	{
		TargetPawn = nullptr;
		bIsSeePlayer = false;
	}
}