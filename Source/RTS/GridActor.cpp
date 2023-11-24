#include "GridActor.h"
#include "RTSGameInstance.h"
#include "Components/InstancedStaticMeshComponent.h"
#include "Kismet/GameplayStatics.h"

AGridActor::AGridActor()
{
	PrimaryActorTick.bCanEverTick = false;
	
	MeshToInstance=CreateDefaultSubobject<UInstancedStaticMeshComponent>(TEXT("InstancedStaticMeshComponent"));
	MeshToInstance->SetupAttachment(RootComponent);
	
	ConstructorHelpers::FObjectFinder<UStaticMesh> StaticMesh(TEXT("/Game/Maps/_GENERATED/FurkanBULBUL/GridMesh"));
	MeshToInstance->SetStaticMesh(StaticMesh.Object);
}

FVector AGridActor::GetRandomUnoccupiedGridLocation()
{
	FVector RandomLocation;
	do
	{
		RandomLocation.X=FMath::RandRange(0,GridSizeX-1)*CellSize;
		RandomLocation.Y=FMath::RandRange(0,GridSizeY-1)*CellSize;
		RandomLocation.Z=0.0f;
	}while (OccupiedGridLocations.Contains(RandomLocation));

	OccupiedGridLocations.Add(RandomLocation);
	return RandomLocation;
}

void AGridActor::BeginPlay()
{
	Super::BeginPlay();
	float colorvalue = 0;
	int index=0;
	
	if (URTSGameInstance* GameInstance = Cast<URTSGameInstance>(UGameplayStatics::GetGameInstance(GetWorld())))
	{
		FVector2D GridSizes = GameInstance->GetGridSizes();
		GridSizeX=GridSizes.X;
		GridSizeY=GridSizes.Y;
	}
	if (MeshToInstance)
	{
		MeshToInstance->ClearInstances();
		MeshToInstance->NumCustomDataFloats=1;

		InstanceLocations.Empty();

		for (int32 Row = 0; Row < GridSizeX; ++Row)
		{
			for (int32 Column = 0; Column < GridSizeY; ++Column)
			{
				FVector LocalPosition=FVector(Row*CellSize,Column*CellSize,0.f);
				FTransform InstanceTransform = FTransform(LocalPosition);
				index = GridSizeY*Row+Column;
				colorvalue = (Row+Column)%2;
				MeshToInstance->AddInstance(InstanceTransform, true);
				MeshToInstance->SetCustomDataValue(index,0,colorvalue);
				
				FVector WorldPosition= GetTransform().TransformPosition(LocalPosition);
				InstanceLocations.Add(WorldPosition);
				//UE_LOG(LogTemp,Warning,TEXT("Index value is : %d"),index)
			}
		}
	}
}
