#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/BoxComponent.h"
#include "EnemySpawner.generated.h"

UCLASS()
class PROJECT_NULL_API AEnemySpawner : public AActor
{
	GENERATED_BODY()

public:
	AEnemySpawner();

protected:
	virtual void BeginPlay() override;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawning")
	TSubclassOf<ACharacter> EnemyBlueprint;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawning")
	int32 MaxEnemies = 5;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawning")
	FVector SpawnAreaSize = FVector(500.0f, 500.0f, 100.0f);

	UPROPERTY(VisibleAnywhere, Category = "Components")
	UBoxComponent* TriggerBox;

	UFUNCTION()
	void SpawnEnemies();

	UFUNCTION()
	void OnOverlapBegin(
		UPrimitiveComponent* OverlappedComponent,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex,
		bool bFromSweep,
		const FHitResult& SweepResult
	);

	UFUNCTION()
	void OnEnemyDeath(AActor* DeadEnemy);

	UFUNCTION(BlueprintCallable, Category = "Spawning")
	void CheckEnemiesAlive();

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Spawning")
	int32 EnemiesSpawned = 0;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Spawning")
	int32 AliveEnemies = 0;

private:
	bool bHasSpawned = false;
	FTimerHandle TimerHandle;
	void SpawnEnemy();
};
