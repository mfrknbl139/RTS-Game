#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "RTS_PlayerController.generated.h"

UCLASS()
class RTS_API ARTS_PlayerController : public APlayerController
{
	GENERATED_BODY()

protected:
	virtual void SetupInputComponent() override;

	// Method to handle the "SpawnSoldiers" action
	void OnSpawnSoldiers();
	FVector SpawnLocation;
	FRotator SpawnRotator=FRotator(0.f,0.f,0.f);
	TArray<FVector> OccupiedLocations;
public:
	bool IsLocationFree(FVector,float);
	
};