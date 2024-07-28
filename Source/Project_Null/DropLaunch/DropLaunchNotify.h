#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "DropLaunchNotify.generated.h"

UCLASS()
class PROJECT_NULL_API UDropLaunchNotify : public UAnimNotify
{
	GENERATED_BODY()

public:
	// Launch impulse
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Launch")
	FVector LaunchImpulse;

	// Line trace distance
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Launch")
	float TraceDistance;

	// 局聪皋捞记 根鸥林
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation")
	UAnimMontage* LaunchMontage;

	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) override;
};
