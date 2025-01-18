#include "MyUserWidget.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"

void UMyUserWidget::NativeConstruct()
{
	Super::NativeConstruct();

	// RestartButton Ŭ�� �̺�Ʈ ����
	if (RestartButton)
	{
		RestartButton->OnClicked.AddDynamic(this, &UMyUserWidget::OnRestartButtonClicked);
	}

	// MainMenuButton Ŭ�� �̺�Ʈ ����
	if (MainMenuButton)
	{
		MainMenuButton->OnClicked.AddDynamic(this, &UMyUserWidget::OnMainMenuButtonClicked);
	}
}

void UMyUserWidget::OnRestartButtonClicked()
{
	UWorld* World = GetWorld();
	if (World)
	{
		FString CurrentLevelName = World->GetMapName();
		CurrentLevelName.RemoveFromStart(World->StreamingLevelsPrefix);

		FName LevelName(*CurrentLevelName);
		UGameplayStatics::OpenLevel(this, LevelName);

		// �Է� ��� ����
		APlayerController* PlayerController = World->GetFirstPlayerController();
		if (PlayerController)
		{
			PlayerController->SetInputMode(FInputModeGameOnly());
			PlayerController->bShowMouseCursor = false;

			APawn* PlayerPawn = PlayerController->GetPawn();
			if (PlayerPawn)
			{
				PlayerController->Possess(PlayerPawn);
				PlayerPawn->EnableInput(PlayerController);
			}
		}
	}
}

void UMyUserWidget::OnMainMenuButtonClicked()
{
	UWorld* World = GetWorld();
	if (World)
	{
		// MainMenuMap���� �̵�
		FName MainMenuMapName(TEXT("MainMenuMap"));
		UGameplayStatics::OpenLevel(this, MainMenuMapName);

		// ���� �ε� �� �Է� ��� ����
		World->GetTimerManager().SetTimerForNextTick([World]() {
			APlayerController* PlayerController = World->GetFirstPlayerController();
			if (PlayerController)
			{
				PlayerController->SetInputMode(FInputModeUIOnly()); // UI ���� �Է� ��� ����
				PlayerController->bShowMouseCursor = true;
			}
			});
	}
}

