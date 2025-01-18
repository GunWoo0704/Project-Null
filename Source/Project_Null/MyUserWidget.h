#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MyUserWidget.generated.h"

UCLASS()
class PROJECT_NULL_API UMyUserWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual void NativeConstruct() override;

protected:
	UFUNCTION()
	void OnRestartButtonClicked();

	UFUNCTION()
	void OnMainMenuButtonClicked();

private:
	UPROPERTY(meta = (BindWidget))
	class UButton* RestartButton;

	UPROPERTY(meta = (BindWidget))
	class UButton* MainMenuButton;
};
