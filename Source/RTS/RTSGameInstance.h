#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "RTSGameInstance.generated.h"

UCLASS()
class RTS_API URTSGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	FORCEINLINE	void SetGridSizes(FVector2d GridSizes){GridSizeX=GridSizes.X; GridSizeY=GridSizes.Y;}
	FORCEINLINE FVector2d GetGridSizes(){return FVector2d(GridSizeX,GridSizeY);}
	FORCEINLINE void SetArmySizes(uint32 NewArmySize){ArmySize = NewArmySize;}
	FORCEINLINE uint16 GetArmySizes(){return ArmySize;}

	void SetGridSizes(int32 NewGridSizeX, int32 NewGridSizeY);
	TArray<FVector> OccupiedLocations;


	//UE_LOG(LogTemp, Warning, TEXT("Does GridSizes Set"));
	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("ArmySize has been generated."));
	
private:
	UPROPERTY()
	uint8 GridSizeX;
	UPROPERTY()
	uint8 GridSizeY;
	UPROPERTY()
	uint32 ArmySize;
};
