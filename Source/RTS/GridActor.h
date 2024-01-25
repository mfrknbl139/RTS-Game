#pragma once

#include <vector>

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GridActor.generated.h"

UCLASS()
class RTS_API AGridActor : public AActor
{
	GENERATED_BODY()
public:	
	AGridActor();
	const TArray<FVector>& GetInstanceLocations() const {return InstanceLocations;}
	FVector GetRandomUnoccupiedGridLocation();
	TArray<FVector> OccupiedGridLocations;
	bool IsLocationOccupied(int32 X,int32 Y);
	void SetLocationOccupied(int32 X, int32 Y,bool bIsOccupied);

	
	uint8 GridSizeX = 100;
	uint8 GridSizeY = 100;
	float CellSize = 1000.f;
protected:
	virtual void BeginPlay() override;


private:	
	UPROPERTY(EditAnywhere)
	class UInstancedStaticMeshComponent* MeshToInstance;
	TArray<FVector> InstanceLocations;
	
	TArray<bool> GridOccupancy;
};
