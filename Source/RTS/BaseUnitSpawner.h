// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BaseUnitSpawner.generated.h"

UCLASS()
class RTS_API ABaseUnitSpawner : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABaseUnitSpawner();
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void SpawnActorAtLocation(FVector Location);

	UPROPERTY(EditAnywhere,Category="Spawn")
	TSubclassOf<AActor> ActorToSpawn;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	/**
	 * 
	 */
	class UInstancedStaticMeshComponent* MeshToInstance;
	

};
