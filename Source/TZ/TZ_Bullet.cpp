#include "TZ_Bullet.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Kismet/GameplayStatics.h"
#include "AC_Heath.h"

// --------------------------------------------------------------------------------
ATZ_Bullet::ATZ_Bullet()
{
	PrimaryActorTick.bCanEverTick = true;

	// Create Collision
	CollisionComponent = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComponent"));
	RootComponent = CollisionComponent;
	CollisionComponent->InitSphereRadius(15.0f);
	CollisionComponent->SetCollisionProfileName("BlockAllDynamic");
	CollisionComponent->SetNotifyRigidBodyCollision(true);
	CollisionComponent->OnComponentHit.AddDynamic(this, &ATZ_Bullet::OnHit);

	// Create Mesh
	BulletMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BulletMesh"));
	BulletMesh->SetupAttachment(RootComponent);
	BulletMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	// Create Projectile Movement
	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovement"));
	ProjectileMovement->InitialSpeed = 2000.f;
	ProjectileMovement->MaxSpeed = 2000.f;
	ProjectileMovement->bRotationFollowsVelocity = true;
	ProjectileMovement->bShouldBounce = false;
	ProjectileMovement->ProjectileGravityScale = 0.0f;

	
}

// --------------------------------------------------------------------------------
// Event Begin Play
void ATZ_Bullet::BeginPlay()
{
	Super::BeginPlay();
	
	if (FireSound)
	{
		UGameplayStatics::PlaySoundAtLocation(this, FireSound, GetActorLocation());
	}
}

// --------------------------------------------------------------------------------
// Event Tick
void ATZ_Bullet::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// --------------------------------------------------------------------------------
// Event Hit
void ATZ_Bullet::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	if (OtherActor && OtherActor != this)
	{
		UAC_Heath* Health = OtherActor->GetComponentByClass<UAC_Heath>();

		if (Health)
			Health->TakeDamage(Damage);

		Destroy();
	}
}

// --------------------------------------------------------------------------------
// Weapon - Setter - Damage
void ATZ_Bullet::SetBulletDamage(float Value)
{
	Damage = Value;
}

