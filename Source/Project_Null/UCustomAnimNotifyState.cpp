// UCustomAnimNotifyState.cpp

#include "UCustomAnimNotifyState.h"
#include "GameFramework/Character.h"
#include "GameFramework/PlayerController.h"
#include "Animation/AnimInstance.h"

void UCustomAnimNotifyState::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration)
{
	Super::NotifyBegin(MeshComp, Animation, TotalDuration);

	// 애님 노티파이의 길이를 설정합니다.
	NotifyDuration = TotalDuration;

	// 메쉬 컴포넌트의 소유자가 캐릭터인지 확인
	if (ACharacter* Character = Cast<ACharacter>(MeshComp->GetOwner()))
	{
		DisableInputAndStopMontages(Character, MeshComp); // 입력 비활성화 및 애니메이션 재생 차단
	}
}

void UCustomAnimNotifyState::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	Super::NotifyEnd(MeshComp, Animation);

	// 메쉬 컴포넌트의 소유자가 캐릭터인지 확인
	if (ACharacter* Character = Cast<ACharacter>(MeshComp->GetOwner()))
	{
		EnableInputAndResumeMontages(Character, MeshComp); // 입력 및 애니메이션 재생 다시 활성화
	}
}

void UCustomAnimNotifyState::DisableInputAndStopMontages(AActor* Actor, USkeletalMeshComponent* MeshComp)
{
	if (APlayerController* PlayerController = Cast<APlayerController>(Actor->GetInstigatorController()))
	{
		// 플레이어 입력 비활성화
		PlayerController->DisableInput(PlayerController);

		// 현재 재생 중인 모든 애니메이션 몽타주 중지
		if (UAnimInstance* AnimInstance = MeshComp->GetAnimInstance())
		{
			AnimInstance->Montage_Stop(0.0f);  // 즉시 모든 몽타주를 중지
		}
	}
}

void UCustomAnimNotifyState::EnableInputAndResumeMontages(AActor* Actor, USkeletalMeshComponent* MeshComp)
{
	if (APlayerController* PlayerController = Cast<APlayerController>(Actor->GetInstigatorController()))
	{
		// 플레이어 입력 활성화
		PlayerController->EnableInput(PlayerController);

		// (필요한 경우) 중지된 애니메이션을 다시 재생하는 코드를 추가할 수 있습니다.
		// 예를 들어, 특정 몽타주를 다시 재생하고 싶다면 여기에 추가하세요.
	}
}
