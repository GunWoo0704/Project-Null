#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "AnimPulse.generated.h"

UCLASS(Blueprintable, meta = (DisplayName = "Push Away Notify"))
class PROJECT_NULL_API UPushAwayNotify : public UAnimNotify
{
	GENERATED_BODY()

public:
	// 애니메이션 노티파이 실행 시 호출되는 함수
	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) override;

	// 애니메이션 에디터에서 설정할 수 있는 변수
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Push Away Settings")
	float PushRadius = 100.0f;  // 기본 범위 설정

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Push Away Settings")
	float PushStrength = 1000.0f;  // 기본 밀어내기 힘

private:
	void PushAwayCharacters(ACharacter* Initiator);
};
