#include "PickUpActor/TZ_BasePickUpActor.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SphereComponent.h"
#include "Components/TextRenderComponent.h"

// --------------------------------------------------------------------------------
ATZ_BasePickUpActor::ATZ_BasePickUpActor()
{
	PrimaryActorTick.bCanEverTick = true;


	// Create Mesh
	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComponent"));
	RootComponent = MeshComponent;

	// Create SphereComponent
	SphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComponent"));
	SphereComponent->InitSphereRadius(100.f);
	SphereComponent->SetCollisionProfileName(TEXT("Trigger"));
	SphereComponent->SetupAttachment(MeshComponent);

	SphereComponent->OnComponentBeginOverlap.AddDynamic(this, &ATZ_BasePickUpActor::OnOverlapBegin);

	// Create Text Render
	TextComponent = CreateDefaultSubobject<UTextRenderComponent>(TEXT("TextComponent"));
	TextComponent->SetupAttachment(MeshComponent);
	TextComponent->SetHorizontalAlignment(EHTA_Center);
	TextComponent->SetWorldSize(30.f);
}

// --------------------------------------------------------------------------------
// Event Begin Play
void ATZ_BasePickUpActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// --------------------------------------------------------------------------------
// Event Tick
void ATZ_BasePickUpActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// --------------------------------------------------------------------------------
// Callback Sphere Collision - Begin Overlap
void ATZ_BasePickUpActor::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (!OtherActor && OtherActor == this) return;
}
