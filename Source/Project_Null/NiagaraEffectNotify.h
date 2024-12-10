#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "NiagaraSystem.h"
#include "NiagaraEffectNotify.generated.h"

UCLASS()
class PROJECT_NULL_API UNiagaraEffectNotify : public UAnimNotify
{
	GENERATED_BODY()

public:
	// ����Ʈ ���ø� (Niagara �ý���)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Effect")
	UNiagaraSystem* EffectTemplate;

	// ����Ʈ �ݰ�
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Effect")
	float EffectRadius = 500.0f;

	// Notify ȣ�� �� ����Ǵ� �Լ�
	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) override;
};
