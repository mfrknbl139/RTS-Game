// Fill out your copyright notice in the Description page of Project Settings.

#include "BaseUnitSpawner.h"

#include "Components/InstancedStaticMeshComponent.h"

// Sets default valuesmoments
ABaseUnitSpawner::ABaseUnitSpawner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	
	MeshToInstance=CreateDefaultSubobject<UInstancedStaticMeshComponent>(TEXT("InstancedStaticMeshComponent"));
	MeshToInstance->SetupAttachment(RootComponent);
		
	ConstructorHelpers::FObjectFinder<UStaticMesh> StaticMesh(TEXT("/Game/Maps/_GENERATED/FurkanBULBUL/Base"));
	MeshToInstance->SetStaticMesh(StaticMesh.Object);

//DrawDebugSphere(GetWorld(), Location, 50.0f, 32, FColor::Red, true, 10.0f);

}

// Called when the game starts or when spawned
void ABaseUnitSpawner::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABaseUnitSpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABaseUnitSpawner::SpawnActorAtLocation(FVector Location)
{
	if (ActorToSpawn != nullptr)
	{
		FActorSpawnParameters SpawnParams;
		GetWorld()->SpawnActor<AActor>(ActorToSpawn, Location, FRotator::ZeroRotator, SpawnParams);
	}
}

