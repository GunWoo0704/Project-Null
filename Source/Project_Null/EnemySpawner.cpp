#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/BoxComponent.h"
#include "EnemySpawner.h"
#include "GameFramework/Character.h"
#include "Engine/World.h"

AEnemySpawner::AEnemySpawner()
{
	PrimaryActorTick.bCanEverTick = false;

	TriggerBox = CreateDefaultSubobject<UBoxComponent>(TEXT("TriggerBox"));
	RootComponent = TriggerBox;

	TriggerBox->SetBoxExtent(SpawnAreaSize);
	TriggerBox->SetCollisionProfileName(TEXT("Trigger"));

	TriggerBox->OnComponentBeginOverlap.AddDynamic(this, &AEnemySpawner::OnOverlapBegin);
}

void AEnemySpawner::BeginPlay()
{
	Super::BeginPlay();
}

void AEnemySpawner::OnOverlapBegin(
	UPrimitiveComponent* OverlappedComponent,
	AActor* OtherActor,
	UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex,
	bool bFromSweep,
	const FHitResult& SweepResult
)
{
	if (OtherActor && OtherActor->IsA(ACharacter::StaticClass()))
	{
		if (bHasSpawned) return;

		bHasSpawned = true;
		EnemiesSpawned = 0;
		AliveEnemies = 0;
		GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &AEnemySpawner::SpawnEnemy, 0.2f, true);
	}
}

void AEnemySpawner::SpawnEnemy()
{
	if (!EnemyBlueprint || EnemiesSpawned >= MaxEnemies)
	{
		GetWorld()->GetTimerManager().ClearTimer(TimerHandle);
		return;
	}

	FVector SpawnLocation = GetActorLocation() + FVector(
		FMath::RandRange(-SpawnAreaSize.X / 2, SpawnAreaSize.X / 2),
		FMath::RandRange(-SpawnAreaSize.Y / 2, SpawnAreaSize.Y / 2),
		0.0f
	);

	FRotator SpawnRotation = FRotator::ZeroRotator;

	ACharacter* SpawnedEnemy = GetWorld()->SpawnActor<ACharacter>(EnemyBlueprint, SpawnLocation, SpawnRotation);

	if (SpawnedEnemy)
	{
		EnemiesSpawned++;
		AliveEnemies++;
	}
}

void AEnemySpawner::OnEnemyDeath(AActor* DeadEnemy)
{
	if (DeadEnemy)
	{
		AliveEnemies--;
		CheckEnemiesAlive();
	}
}

void AEnemySpawner::CheckEnemiesAlive()
{
	if (AliveEnemies <= 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("All enemies are dead. Unlocking area."));
	}
}
void AEnemySpawner::SpawnEnemies()
{
	if (!EnemyBlueprint || MaxEnemies <= 0)
		return;

	for (int32 i = 0; i < MaxEnemies; i++)
	{
		SpawnEnemy();
	}
}
