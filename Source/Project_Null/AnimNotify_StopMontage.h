// AnimNotify_StopMontage.h

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "AnimNotify_StopMontage.generated.h" // 이 줄을 맨 마지막으로 이동

UCLASS()
class PROJECT_NULL_API UAnimNotify_StopMontage : public UAnimNotify
{
	GENERATED_BODY()

public:
	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) override;
};
