#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameFramework/Character.h"
#include "CollisionHandlingActor.generated.h"

UCLASS()
class PROJECT_NULL_API ACollisionHandlingActor : public AActor
{
	GENERATED_BODY()

public:
	ACollisionHandlingActor();

protected:
	virtual void BeginPlay() override;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Teleport")
	FVector TargetLocation; // ĳ���Ͱ� �̵��� ��ġ

	// �浹�� ó���� �Լ�
	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

private:
	UPROPERTY(VisibleAnywhere, Category = "Collision")
	class UBoxComponent* CollisionBox;
};
