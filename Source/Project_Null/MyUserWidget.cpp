#include "MyUserWidget.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"

void UMyUserWidget::NativeConstruct()
{
	Super::NativeConstruct();

	// RestartButton 클릭 이벤트 연결
	if (RestartButton)
	{
		RestartButton->OnClicked.AddDynamic(this, &UMyUserWidget::OnRestartButtonClicked);
	}

	// MainMenuButton 클릭 이벤트 연결
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

		// 입력 모드 설정
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
		// MainMenuMap으로 이동
		FName MainMenuMapName(TEXT("MainMenuMap"));
		UGameplayStatics::OpenLevel(this, MainMenuMapName);

		// 레벨 로드 후 입력 모드 설정
		World->GetTimerManager().SetTimerForNextTick([World]() {
			APlayerController* PlayerController = World->GetFirstPlayerController();
			if (PlayerController)
			{
				PlayerController->SetInputMode(FInputModeUIOnly()); // UI 전용 입력 모드 설정
				PlayerController->bShowMouseCursor = true;
			}
			});
	}
}

