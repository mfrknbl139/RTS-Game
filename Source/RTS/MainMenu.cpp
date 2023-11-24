
#include "MainMenu.h"
#include "RTSGameInstance.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/KismetTextLibrary.h"

void UMainMenu::NativeConstruct()
{
	Super::NativeConstruct();
	
	IncreasePack->OnClicked.AddDynamic(this, &UMainMenu::IncreaseAmount);
	DecreasePack->OnClicked.AddDynamic(this, &UMainMenu::DecreaseAmount);
	IncreaseGX->OnClicked.AddDynamic(this, &UMainMenu::IncreaseGridX);
	DecreaseGX->OnClicked.AddDynamic(this, &UMainMenu::DecreaseGridX);
	IncreaseGY->OnClicked.AddDynamic(this, &UMainMenu::IncreaseGridY);
	DecreaseGY->OnClicked.AddDynamic(this, &UMainMenu::DecreaseGridY);
	PlayGame->OnClicked.AddDynamic(this,&UMainMenu::UMainMenu::Play);
	QuitGame->OnClicked.AddDynamic(this,&UMainMenu::Quit);
}
void UMainMenu::NativeOnMouseLeave(const FPointerEvent& InMouseEvent) //overriding cursor so that it does not disappear.
{
	Super::NativeOnMouseLeave(InMouseEvent);
	
	APlayerController* PlayerController = GetOwningPlayer();
	if (PlayerController)
	{
		PlayerController->bShowMouseCursor = true; // Shows the cursor when mouse leaves the widget area
	}
}
void UMainMenu::IncreaseAmount()
{
	Amount= UKismetMathLibrary::Min(Amount+10,500);
	AmountText->SetText(UKismetTextLibrary::Conv_IntToText(Amount));
}
void UMainMenu::DecreaseAmount()
{
	Amount= UKismetMathLibrary::Max(Amount-10,10);
	AmountText->SetText(UKismetTextLibrary::Conv_IntToText(Amount));
}
void UMainMenu::IncreaseGridX()
{
	AmountGridX= UKismetMathLibrary::Min(AmountGridX+1,100);
	AmountTextX->SetText(UKismetTextLibrary::Conv_IntToText(AmountGridX));
}
void UMainMenu::DecreaseGridX()
{
	AmountGridX= UKismetMathLibrary::Max(AmountGridX-1,1);
	AmountTextX->SetText(UKismetTextLibrary::Conv_IntToText(AmountGridX));
}
void UMainMenu::IncreaseGridY()
{
	AmountGridY= UKismetMathLibrary::Min(AmountGridY+1,100);
	AmountTextY->SetText(UKismetTextLibrary::Conv_IntToText(AmountGridY));
}
void UMainMenu::DecreaseGridY()
{
	AmountGridY= UKismetMathLibrary::Max(AmountGridY-1,1);
	AmountTextY->SetText(UKismetTextLibrary::Conv_IntToText(AmountGridY));
}
void UMainMenu::Play()
{
	URTSGameInstance* GameInstance = Cast<URTSGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	if (GameInstance)
	{
		GameInstance->SetGridSizes(FVector2d(AmountGridX,AmountGridY));
		GameInstance->SetArmySizes(Amount);
		UGameplayStatics::OpenLevel(GetWorld(),FName ("WarScene"),true);
	}
}
void UMainMenu::Quit()
{
	APlayerController* PlayerController=GetWorld()-> GetFirstPlayerController();
	if (PlayerController)
	{
		PlayerController->ConsoleCommand("quit");
	}
}



