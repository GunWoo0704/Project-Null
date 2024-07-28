// CheckIfGrounded.h

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "CheckIfGrounded.generated.h"

UCLASS()
class PROJECT_NULL_API UCheckIfGrounded : public UAnimNotify
{
	GENERATED_BODY()

public:
	// 다음 몽타주를 지정할 수 있는 변수
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation")
	UAnimMontage* NextMontage;

	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) override;

private:
	bool IsCharacterOnGround(ACharacter* Character);
};
