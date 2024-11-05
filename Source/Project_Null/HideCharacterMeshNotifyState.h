#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotifyState.h"
#include "HideCharacterMeshNotifyState.generated.h"

UCLASS()
class PROJECT_NULL_API UHideCharacterMeshNotifyState : public UAnimNotifyState
{
	GENERATED_BODY()

public:
	virtual void NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration) override;
	virtual void NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) override;

private:
	// Helper function to set visibility recursively
	void SetMeshVisibilityRecursively(USceneComponent* Component, bool bVisible);
};
