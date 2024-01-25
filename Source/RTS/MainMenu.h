#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MainMenu.generated.h"

class UButton;
class UTextBlock;
UCLASS()
class RTS_API UMainMenu : public UUserWidget
{
	GENERATED_BODY()
public:
	virtual void NativeConstruct() override;
	virtual void NativeOnMouseLeave(const FPointerEvent& InMouseEvent) override;
	virtual FReply NativeOnKeyDown(const FGeometry& InGeometry, const FKeyEvent& InKeyEvent) override;

protected:

	UPROPERTY()
	uint16 M_PackSize=10;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Grid")
	uint8 M_SizeGridX=5;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Grid")
	uint8 M_SizeGridY=5;
	
	UPROPERTY(meta=(BindWidget))
	UButton* IncreasePack;
	UPROPERTY(meta=(BindWidget))
	UButton* DecreasePack;
	UPROPERTY(meta=(BindWidget))
	UTextBlock* AmountText;
	UPROPERTY(meta=(BindWidget))
	UButton* IncreaseGX;
	UPROPERTY(meta=(BindWidget))
	UButton* DecreaseGX;
	UPROPERTY(meta=(BindWidget))
	UTextBlock* AmountTextX;
	UPROPERTY(meta=(BindWidget))
	UTextBlock* AmountTextY;
	UPROPERTY(meta=(BindWidget))
	UButton* IncreaseGY;
	UPROPERTY(meta=(BindWidget))
	UButton* DecreaseGY;
	
	UPROPERTY(meta=(BindWidget))
	UButton* PlayGame;
	UPROPERTY(meta=(BindWidget))
	UButton* QuitGame;
	
	UFUNCTION()
	void IncreaseAmount();
	UFUNCTION()
	void DecreaseAmount();
	UFUNCTION()
	void IncreaseGridX();
	UFUNCTION()
	void DecreaseGridX();
	UFUNCTION()
	void IncreaseGridY();
	UFUNCTION()
	void DecreaseGridY();
	UFUNCTION()
	void Play();
	UFUNCTION()
	void Quit();
};
