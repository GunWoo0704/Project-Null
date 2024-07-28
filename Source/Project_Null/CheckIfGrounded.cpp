// CheckIfGrounded.cpp

#include "CheckIfGrounded.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Animation/AnimInstance.h"

void UCheckIfGrounded::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	if (MeshComp && MeshComp->GetOwner())
	{
		ACharacter* Character = Cast<ACharacter>(MeshComp->GetOwner());
		if (Character)
		{
			UAnimInstance* AnimInstance = MeshComp->GetAnimInstance();
			if (IsCharacterOnGround(Character))
			{
				if (AnimInstance)
				{
					// 현재 몽타주 멈춤
					AnimInstance->Montage_Stop(0.2f); // 페이드 아웃 시간

					// 다음 몽타주 재생
					if (NextMontage)
					{
						AnimInstance->Montage_Play(NextMontage);
					}
				}
			}
			else
			{
				if (AnimInstance)
				{
					// 루프 섹션으로 이동
					FName LoopSectionName = FName("Loop");
					if (AnimInstance->Montage_GetCurrentSection() != LoopSectionName)
					{
						AnimInstance->Montage_JumpToSection(LoopSectionName, AnimInstance->GetCurrentActiveMontage());
					}
				}
			}
		}
	}
}

bool UCheckIfGrounded::IsCharacterOnGround(ACharacter* Character)
{
	if (Character && Character->GetCharacterMovement())
	{
		return Character->GetCharacterMovement()->IsMovingOnGround();
	}
	return false;
}
