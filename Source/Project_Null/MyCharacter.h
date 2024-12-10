#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "MyCharacter.generated.h"

UCLASS()
class PROJECT_NULL_API AMyCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// ������
	AMyCharacter();

protected:
	// ���� ���� �� ȣ��
	virtual void BeginPlay() override;

public:
	// �� ������ ȣ��
	virtual void Tick(float DeltaTime) override;

	// �������Ʈ���� ȣ�� ������ �Լ� - ��� ĳ���� ����
	UFUNCTION(BlueprintCallable, Category = "Custom", meta = (DisplayName = "Freeze All Other Characters"))
	void FreezeAllOtherCharacters();

	// �������Ʈ���� ȣ�� ������ �Լ� - ��� ĳ���� �ٽ� Ȱ��ȭ
	UFUNCTION(BlueprintCallable, Category = "Custom", meta = (DisplayName = "Unfreeze All Other Characters"))
	void UnfreezeAllOtherCharacters();
};
