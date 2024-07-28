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
	// ���� ��Ÿ�ָ� ������ �� �ִ� ����
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation")
	UAnimMontage* NextMontage;

	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) override;

private:
	bool IsCharacterOnGround(ACharacter* Character);
};
