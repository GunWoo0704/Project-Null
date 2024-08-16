// UCustomAnimNotifyState.h

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotifyState.h"
#include "UCustomAnimNotifyState.generated.h"

UCLASS()
class PROJECT_NULL_API UCustomAnimNotifyState : public UAnimNotifyState
{
	GENERATED_BODY()

public:
	// 노티파이 시작 시 호출
	virtual void NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration) override;

	// 노티파이 끝날 때 호출
	virtual void NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) override;

	// 노티파이의 재생 길이를 설정하는 프로퍼티
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Notify")
	float NotifyDuration;

private:
	// 플레이어 입력 및 애니메이션 재생 차단하는 함수
	void DisableInputAndStopMontages(AActor* Actor, USkeletalMeshComponent* MeshComp);

	// 플레이어 입력 및 애니메이션 재생 다시 활성화하는 함수
	void EnableInputAndResumeMontages(AActor* Actor, USkeletalMeshComponent* MeshComp);
};
