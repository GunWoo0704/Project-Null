#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotifyState.h"
#include "InputDisable.generated.h"

/**
 * A custom AnimNotifyState to disable player input during the animation state.
 */
UCLASS()
class PROJECT_NULL_API UInputDisable : public UAnimNotifyState
{
	GENERATED_BODY()

public:
	// Called when the animation notify state begins
	virtual void NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration) override;

	// Called when the animation notify state ends
	virtual void NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) override;
};
