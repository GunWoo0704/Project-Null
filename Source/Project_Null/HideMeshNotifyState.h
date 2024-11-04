#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotifyState.h"
#include "HideMeshNotifyState.generated.h"

UCLASS()
class PROJECT_NULL_API UHideMeshNotifyState : public UAnimNotifyState
{
	GENERATED_BODY()

public:
	// ����� �޼��� �ñ״�ó�� �°� ����
	virtual void NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration, const FAnimNotifyEventReference& EventReference) override;
	virtual void NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference) override;
};
