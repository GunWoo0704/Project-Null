#include "NiagaraEffectNotify.h"
#include "NiagaraFunctionLibrary.h"
#include "GameFramework/Actor.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/World.h"
#include "DrawDebugHelpers.h" // 디버깅용 헤더

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

	// 월드 컨텍스트 가져오기
	UWorld* World = Owner->GetWorld();
	if (!World)
	{
		UE_LOG(LogTemp, Error, TEXT("World is null."));
		return;
	}

	FVector OwnerLocation = Owner->GetActorLocation();

	// 디버그: 스피어 확인
	DrawDebugSphere(World, OwnerLocation, EffectRadius, 32, FColor::Red, false, 2.0f);
	UE_LOG(LogTemp, Warning, TEXT("Debug Sphere Drawn at Location: %s with Radius: %f"), *OwnerLocation.ToString(), EffectRadius);

	// 스피어 오버랩으로 범위 내 액터 찾기
	TArray<FOverlapResult> OverlapResults;
	FCollisionQueryParams QueryParams;
	QueryParams.AddIgnoredActor(Owner); // 소유자 제외

	FCollisionShape CollisionShape;
	CollisionShape.SetSphere(EffectRadius);

	bool bHasOverlaps = World->OverlapMultiByChannel(
		OverlapResults,
		OwnerLocation,
		FQuat::Identity,
		ECC_Pawn, // Pawn 채널 사용
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

				// 나이아가라 이펙트 스폰
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
