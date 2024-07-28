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
					// ���� ��Ÿ�� ����
					AnimInstance->Montage_Stop(0.2f); // ���̵� �ƿ� �ð�

					// ���� ��Ÿ�� ���
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
					// ���� �������� �̵�
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
