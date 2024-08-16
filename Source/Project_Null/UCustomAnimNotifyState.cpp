// UCustomAnimNotifyState.cpp

#include "UCustomAnimNotifyState.h"
#include "GameFramework/Character.h"
#include "GameFramework/PlayerController.h"
#include "Animation/AnimInstance.h"

void UCustomAnimNotifyState::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration)
{
	Super::NotifyBegin(MeshComp, Animation, TotalDuration);

	// �ִ� ��Ƽ������ ���̸� �����մϴ�.
	NotifyDuration = TotalDuration;

	// �޽� ������Ʈ�� �����ڰ� ĳ�������� Ȯ��
	if (ACharacter* Character = Cast<ACharacter>(MeshComp->GetOwner()))
	{
		DisableInputAndStopMontages(Character, MeshComp); // �Է� ��Ȱ��ȭ �� �ִϸ��̼� ��� ����
	}
}

void UCustomAnimNotifyState::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	Super::NotifyEnd(MeshComp, Animation);

	// �޽� ������Ʈ�� �����ڰ� ĳ�������� Ȯ��
	if (ACharacter* Character = Cast<ACharacter>(MeshComp->GetOwner()))
	{
		EnableInputAndResumeMontages(Character, MeshComp); // �Է� �� �ִϸ��̼� ��� �ٽ� Ȱ��ȭ
	}
}

void UCustomAnimNotifyState::DisableInputAndStopMontages(AActor* Actor, USkeletalMeshComponent* MeshComp)
{
	if (APlayerController* PlayerController = Cast<APlayerController>(Actor->GetInstigatorController()))
	{
		// �÷��̾� �Է� ��Ȱ��ȭ
		PlayerController->DisableInput(PlayerController);

		// ���� ��� ���� ��� �ִϸ��̼� ��Ÿ�� ����
		if (UAnimInstance* AnimInstance = MeshComp->GetAnimInstance())
		{
			AnimInstance->Montage_Stop(0.0f);  // ��� ��� ��Ÿ�ָ� ����
		}
	}
}

void UCustomAnimNotifyState::EnableInputAndResumeMontages(AActor* Actor, USkeletalMeshComponent* MeshComp)
{
	if (APlayerController* PlayerController = Cast<APlayerController>(Actor->GetInstigatorController()))
	{
		// �÷��̾� �Է� Ȱ��ȭ
		PlayerController->EnableInput(PlayerController);

		// (�ʿ��� ���) ������ �ִϸ��̼��� �ٽ� ����ϴ� �ڵ带 �߰��� �� �ֽ��ϴ�.
		// ���� ���, Ư�� ��Ÿ�ָ� �ٽ� ����ϰ� �ʹٸ� ���⿡ �߰��ϼ���.
	}
}
