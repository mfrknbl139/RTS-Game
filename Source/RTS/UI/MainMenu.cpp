
#include "MainMenu.h"
#include "RTS/RTSGameInstance.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/KismetTextLibrary.h"

#include "Input/Reply.h"

#include "Framework/Application/SlateApplication.h"
#include "Framework/Commands/Commands.h"
#include "Framework/Application/SlateApplication.h"

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


	// Bu widget'ın focus alabilmesini sağla
	//this->bIsFocusable = true;

	/* Focus'u bu widget'a ayarla
	if (APlayerController* PC = GetOwningPlayer())
	{
		FInputModeUIOnly InputMode;
		InputMode.SetWidgetToFocus(this->TakeWidget());
		InputMode.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
		PC->SetInputMode(InputMode);
		PC->bShowMouseCursor = true;

		// Bu widget'a odaklan
		this->SetUserFocus(PC);
	}*/
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

FReply UMainMenu::NativeOnKeyDown(const FGeometry& InGeometry, const FKeyEvent& InKeyEvent)
{
	// Eğer Enter tuşuna basıldıysa, Play fonksiyonunu çağır
		if (InKeyEvent.GetKey() == EKeys::Enter)
		{
			Play();
			return FReply::Handled();  // Olayın işlendiğini belirt
			}
	// Varsayılan işlemi yap (diğer tuşlara basıldığında)
	return Super::NativeOnKeyDown(InGeometry, InKeyEvent);
}

void UMainMenu::IncreaseAmount()
{
	M_PackSize= UKismetMathLibrary::Min(M_PackSize+10,500);
	AmountText->SetText(UKismetTextLibrary::Conv_IntToText(M_PackSize));
}
void UMainMenu::DecreaseAmount()
{
	M_PackSize= UKismetMathLibrary::Max(M_PackSize-10,10);
	AmountText->SetText(UKismetTextLibrary::Conv_IntToText(M_PackSize));
}
void UMainMenu::IncreaseGridX()
{
	M_SizeGridX= UKismetMathLibrary::Min(M_SizeGridX+1,100);
	AmountTextX->SetText(UKismetTextLibrary::Conv_IntToText(M_SizeGridX));
}
void UMainMenu::DecreaseGridX()
{
	M_SizeGridX= UKismetMathLibrary::Max(M_SizeGridX-1,1);
	AmountTextX->SetText(UKismetTextLibrary::Conv_IntToText(M_SizeGridX));
}
void UMainMenu::IncreaseGridY()
{
	M_SizeGridY= UKismetMathLibrary::Min(M_SizeGridY+1,100);
	AmountTextY->SetText(UKismetTextLibrary::Conv_IntToText(M_SizeGridY));
}
void UMainMenu::DecreaseGridY()
{
	M_SizeGridY= UKismetMathLibrary::Max(M_SizeGridY-1,1);
	AmountTextY->SetText(UKismetTextLibrary::Conv_IntToText(M_SizeGridY));
}
void UMainMenu::Play()
{
	URTSGameInstance* GameInstance = Cast<URTSGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	if (GameInstance)
	{
		GameInstance->SetGridSizes(FVector2d(M_SizeGridX,M_SizeGridY));
		GameInstance->SetArmySizes(M_PackSize);
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



