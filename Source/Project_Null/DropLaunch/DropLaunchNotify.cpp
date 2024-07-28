#include "DropLaunchNotify.h"
#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/World.h"
#include "DrawDebugHelpers.h"

void UDropLaunchNotify::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	if (MeshComp && MeshComp->GetOwner())
	{
		ACharacter* OwnerCharacter = Cast<ACharacter>(MeshComp->GetOwner());
		if (OwnerCharacter)
		{
			// 라인 트레이스 시작점과 끝점 설정
			FVector Start = OwnerCharacter->GetActorLocation();
			FVector ForwardVector = OwnerCharacter->GetActorForwardVector();
			FVector End = Start + (ForwardVector * TraceDistance);

			FHitResult HitResult;

			// 라인 트레이스 파라미터 설정
			FCollisionQueryParams CollisionParams;
			CollisionParams.AddIgnoredActor(OwnerCharacter);

			// 라인 트레이스 실행
			bool bHit = OwnerCharacter->GetWorld()->LineTraceSingleByChannel(
				HitResult,
				Start,
				End,
				ECC_Visibility,
				CollisionParams
			);

			// 디버그 라인 그리기 (옵션)
			DrawDebugLine(
				OwnerCharacter->GetWorld(),
				Start,
				End,
				FColor::Green,
				false, 5.0f, 0, 1.0f
			);

			if (bHit)
			{
				ACharacter* HitCharacter = Cast<ACharacter>(HitResult.GetActor());
				if (HitCharacter)
				{
					// 적 캐릭터를 발사
					HitCharacter->LaunchCharacter(LaunchImpulse, true, true);

					// 적 캐릭터의 애니메이션을 재생
					UAnimInstance* AnimInstance = HitCharacter->GetMesh()->GetAnimInstance();
					if (AnimInstance && LaunchMontage)
					{
						AnimInstance->Montage_Play(LaunchMontage);
					}
				}
			}
		}
	}
}
