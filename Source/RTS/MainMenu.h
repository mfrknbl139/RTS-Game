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
	
protected:

	UPROPERTY()
	uint16 Amount=10;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Grid")
	uint8 AmountGridX=20;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Grid")
	uint8 AmountGridY=20;
	
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
