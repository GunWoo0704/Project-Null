#include "MyAnimNotifyState_SpeedControl.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"

void UMyAnimNotifyState_SpeedControl::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration)
{
	if (!MeshComp) return;

	// ĳ���� ��������
	ACharacter* Character = Cast<ACharacter>(MeshComp->GetOwner());
	if (Character && Character->GetCharacterMovement())
	{
		// ���ǵ带 �����մϴ�.
		Character->GetCharacterMovement()->MaxWalkSpeed = TargetSpeed;
	}
}

void UMyAnimNotifyState_SpeedControl::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	if (!MeshComp) return;

	// ĳ���� ��������
	ACharacter* Character = Cast<ACharacter>(MeshComp->GetOwner());
	if (Character && Character->GetCharacterMovement())
	{
		// ���ǵ带 ������� �ǵ����ϴ�. (�⺻ ���ǵ�� ������ �ּ���)
		Character->GetCharacterMovement()->MaxWalkSpeed = 600.0f; // �⺻ ���ǵ� ������ ���� ����
	}
}
