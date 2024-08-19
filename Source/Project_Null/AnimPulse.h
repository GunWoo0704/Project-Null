#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "AnimPulse.generated.h"

UCLASS(Blueprintable, meta = (DisplayName = "Push Away Notify"))
class PROJECT_NULL_API UPushAwayNotify : public UAnimNotify
{
	GENERATED_BODY()

public:
	// �ִϸ��̼� ��Ƽ���� ���� �� ȣ��Ǵ� �Լ�
	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) override;

	// �ִϸ��̼� �����Ϳ��� ������ �� �ִ� ����
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Push Away Settings")
	float PushRadius = 100.0f;  // �⺻ ���� ����

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Push Away Settings")
	float PushStrength = 1000.0f;  // �⺻ �о�� ��

private:
	void PushAwayCharacters(ACharacter* Initiator);
};
