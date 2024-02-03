
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Components/BoxComponent.h"

#include "AI_Soldiers.generated.h"

UCLASS()
class RTS_API AAI_Soldiers : public ACharacter
{
	GENERATED_BODY()
private:

public:
	AAI_Soldiers();
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Collision")
	UBoxComponent* SoldiersCollisionBox;
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	void SpawnSoldierInstances(const FVector& SpawnLocation);
	void LogCollisionAndMeshLocations();
	
protected:
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere)
	UInstancedStaticMeshComponent* SoldiersMesh;
	UPROPERTY()
	float PackSize;
	int16 InstanceIndex;
	float Spacing = 100.0f;};
