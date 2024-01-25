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
		TArray<FVector> EmptyLocations;
    
		// Grid üzerindeki tüm konumları kontrol et
		for (int32 Row = 0; Row < GridSizeX; ++Row)
		{
			for (int32 Column = 0; Column < GridSizeY; ++Column)
			{
				if (!IsLocationOccupied(Row, Column)) // Eğer konum boşsa
				{
					// Boş konumu listeye ekle
					EmptyLocations.Add(FVector(Row * CellSize, Column * CellSize, 0.f));
				}
			}
		}
    
		if (EmptyLocations.Num() > 0) // Eğer en az bir boş konum varsa
		{
			// Listeden rastgele bir konum seç
			int32 RandomIndex = FMath::RandRange(0, EmptyLocations.Num() - 1);
			return EmptyLocations[RandomIndex];
		}
    
		// Eğer boş bir konum yoksa, hata değeri döndür
		return FVector(-1, -1, -1);	
	}

bool AGridActor::IsLocationOccupied(int32 X, int32 Y)
	{
		int32 Index = X + Y * GridSizeX;
		if (Index < GridOccupancy.Num())
		{
			return GridOccupancy[Index];
		}
		return false;
	}

void AGridActor::SetLocationOccupied(int32 X, int32 Y, bool bIsOccupied)
	{
		int32 Index = X + Y * GridSizeX;
		if (Index < GridOccupancy.Num())
		{
			GridOccupancy[Index] = bIsOccupied;
		}
	}

void AGridActor::BeginPlay()
{
	Super::BeginPlay();
	if (URTSGameInstance* GameInstance = Cast<URTSGameInstance>(UGameplayStatics::GetGameInstance(GetWorld())))
	{
		GridSizeX = GameInstance->GetGridSizes().X;
		GridSizeY = GameInstance->GetGridSizes().Y;
	}

	GridOccupancy.Init(false, GridSizeX * GridSizeY);
		
	if (MeshToInstance)
	{
		MeshToInstance->ClearInstances();
		MeshToInstance->NumCustomDataFloats = 1;

		InstanceLocations.Empty();

		for (int32 Row = 0; Row < GridSizeX; ++Row)
		{
			for (int32 Column = 0; Column < GridSizeY; ++Column)
			{
					FVector LocalPosition = FVector(Row * CellSize, Column * CellSize, 0.f);
					FTransform InstanceTransform = FTransform(LocalPosition);
					int32 Index = GridSizeY * Row + Column;
					float ColorValue = (Row + Column) % 2;

					MeshToInstance->AddInstance(InstanceTransform, true);
					MeshToInstance->SetCustomDataValue(Index, 0, ColorValue);

					FVector WorldPosition = GetTransform().TransformPosition(LocalPosition);
					InstanceLocations.Add(WorldPosition);

					// Log spawn edilen konumu
					UE_LOG(LogTemp, Warning, TEXT("Spawned at Location X: %f, Y: %f"), WorldPosition.X, WorldPosition.Y);
			}
		}
	}
}
