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
			// ���� Ʈ���̽� �������� ���� ����
			FVector Start = OwnerCharacter->GetActorLocation();
			FVector ForwardVector = OwnerCharacter->GetActorForwardVector();
			FVector End = Start + (ForwardVector * TraceDistance);

			FHitResult HitResult;

			// ���� Ʈ���̽� �Ķ���� ����
			FCollisionQueryParams CollisionParams;
			CollisionParams.AddIgnoredActor(OwnerCharacter);

			// ���� Ʈ���̽� ����
			bool bHit = OwnerCharacter->GetWorld()->LineTraceSingleByChannel(
				HitResult,
				Start,
				End,
				ECC_Visibility,
				CollisionParams
			);

			// ����� ���� �׸��� (�ɼ�)
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
					// �� ĳ���͸� �߻�
					HitCharacter->LaunchCharacter(LaunchImpulse, true, true);

					// �� ĳ������ �ִϸ��̼��� ���
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
