#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "RTS/AI/AI_Soldiers.h"
#include "RTS_PlayerController.generated.h"

UCLASS()
class RTS_API ARTS_PlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	bool IsLocationFree(FVector,float);
	ARTS_PlayerController();
protected:
	AAI_Soldiers* GetSoldiersPack() const;
	void SetSoldierPack(AAI_Soldiers* NewSoldierPack);
	void SomeFunctionToSetSoldierPack();
	virtual void SetupInputComponent() override;
	void OnLeftMouseClick();

	// Method to handle the "SpawnSoldiers" action
	void OnSpawnSoldiers();
	FVector SpawnLocation;
	FRotator SpawnRotator=FRotator(0.f,0.f,0.f);
	TArray<FVector> OccupiedLocations;


private:
	AAI_Soldiers* SoldierPack;
};