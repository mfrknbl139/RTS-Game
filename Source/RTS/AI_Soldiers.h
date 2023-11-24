
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AI_Soldiers.generated.h"

UCLASS()
class RTS_API AAI_Soldiers : public ACharacter
{
	GENERATED_BODY()
private:

public:
	AAI_Soldiers();
	
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	void SpawnSoldierInstances();	

protected:
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere)
	UInstancedStaticMeshComponent* SoldiersMesh;
	UPROPERTY()
	float DistanceBetweenSoldiers=20.0f;
	UPROPERTY()
	float PackSize;
	
};
