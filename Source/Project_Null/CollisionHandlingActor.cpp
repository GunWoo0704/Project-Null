#include "CollisionHandlingActor.h"
#include "Components/BoxComponent.h"
#include "GameFramework/Character.h"

// Sets default values
ACollisionHandlingActor::ACollisionHandlingActor()
{
	// Create a Box Component for collision detection
	CollisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("CollisionBox"));
	RootComponent = CollisionBox;

	// Set default size for the collision box
	CollisionBox->SetBoxExtent(FVector(50.0f, 50.0f, 50.0f));
	CollisionBox->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	CollisionBox->SetCollisionObjectType(ECollisionChannel::ECC_WorldDynamic);
	CollisionBox->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Overlap);

	// Bind the overlap event
	CollisionBox->OnComponentBeginOverlap.AddDynamic(this, &ACollisionHandlingActor::OnOverlapBegin);

	// Default target location
	TargetLocation = FVector(0.0f, 0.0f, 0.0f);
}

// Called when the game starts or when spawned
void ACollisionHandlingActor::BeginPlay()
{
	Super::BeginPlay();
}

// Overlap event
void ACollisionHandlingActor::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	// Check if the overlapping actor is a character
	ACharacter* OverlappingCharacter = Cast<ACharacter>(OtherActor);
	if (OverlappingCharacter)
	{
		// Teleport the character to the target location
		OverlappingCharacter->SetActorLocation(TargetLocation);
	}
}
