#include "MyAnimNotifyState_SpeedControl.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"

void UMyAnimNotifyState_SpeedControl::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration)
{
	if (!MeshComp) return;

	// 캐릭터 가져오기
	ACharacter* Character = Cast<ACharacter>(MeshComp->GetOwner());
	if (Character && Character->GetCharacterMovement())
	{
		// 스피드를 설정합니다.
		Character->GetCharacterMovement()->MaxWalkSpeed = TargetSpeed;
	}
}

void UMyAnimNotifyState_SpeedControl::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	if (!MeshComp) return;

	// 캐릭터 가져오기
	ACharacter* Character = Cast<ACharacter>(MeshComp->GetOwner());
	if (Character && Character->GetCharacterMovement())
	{
		// 스피드를 원래대로 되돌립니다. (기본 스피드로 변경해 주세요)
		Character->GetCharacterMovement()->MaxWalkSpeed = 600.0f; // 기본 스피드 값으로 수정 가능
	}
}
