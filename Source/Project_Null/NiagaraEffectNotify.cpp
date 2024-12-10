#include "NiagaraEffectNotify.h"
#include "NiagaraFunctionLibrary.h"
#include "GameFramework/Actor.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/World.h"
#include "DrawDebugHelpers.h" // ������ ���

void UNiagaraEffectNotify::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	if (!MeshComp || !EffectTemplate)
	{
		UE_LOG(LogTemp, Error, TEXT("MeshComp or EffectTemplate is null."));
		return;
	}

	AActor* Owner = MeshComp->GetOwner();
	if (!Owner)
	{
		UE_LOG(LogTemp, Error, TEXT("Owner is null."));
		return;
	}

	// ���� ���ؽ�Ʈ ��������
	UWorld* World = Owner->GetWorld();
	if (!World)
	{
		UE_LOG(LogTemp, Error, TEXT("World is null."));
		return;
	}

	FVector OwnerLocation = Owner->GetActorLocation();

	// �����: ���Ǿ� Ȯ��
	DrawDebugSphere(World, OwnerLocation, EffectRadius, 32, FColor::Red, false, 2.0f);
	UE_LOG(LogTemp, Warning, TEXT("Debug Sphere Drawn at Location: %s with Radius: %f"), *OwnerLocation.ToString(), EffectRadius);

	// ���Ǿ� ���������� ���� �� ���� ã��
	TArray<FOverlapResult> OverlapResults;
	FCollisionQueryParams QueryParams;
	QueryParams.AddIgnoredActor(Owner); // ������ ����

	FCollisionShape CollisionShape;
	CollisionShape.SetSphere(EffectRadius);

	bool bHasOverlaps = World->OverlapMultiByChannel(
		OverlapResults,
		OwnerLocation,
		FQuat::Identity,
		ECC_Pawn, // Pawn ä�� ���
		CollisionShape,
		QueryParams
	);

	if (bHasOverlaps)
	{
		for (const FOverlapResult& Result : OverlapResults)
		{
			AActor* OverlappedActor = Result.GetActor();

			if (OverlappedActor && OverlappedActor != Owner)
			{
				UE_LOG(LogTemp, Warning, TEXT("Effect spawned for actor: %s"), *OverlappedActor->GetName());

				// ���̾ư��� ����Ʈ ����
				UNiagaraFunctionLibrary::SpawnSystemAtLocation(
					World,
					EffectTemplate,
					OverlappedActor->GetActorLocation()
				);
			}
		}
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("No actors detected in the effect radius."));
	}
}
