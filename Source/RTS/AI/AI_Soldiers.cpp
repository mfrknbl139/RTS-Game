#include "AI_Soldiers.h"

#include "AISoldiersController.h"
#include "Components/InstancedStaticMeshComponent.h"
#include "UObject/ConstructorHelpers.h"
#include "RTS/RTSGameInstance.h"
#include "Kismet/GameplayStatics.h"

AAI_Soldiers::AAI_Soldiers()
{
	PrimaryActorTick.bCanEverTick = false;

	AIControllerClass=AAISoldiersController::StaticClass();//Controller class ataması.
	
	SoldiersMesh = CreateDefaultSubobject<UInstancedStaticMeshComponent>(TEXT("SoldiersMesh"));
	RootComponent=SoldiersMesh;

	SoldiersCollisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("SoldiersCollisionBox"));
	SoldiersCollisionBox->SetupAttachment(RootComponent);
	SoldiersCollisionBox->SetCollisionProfileName(TEXT("SoldierGroup"));
	SoldiersCollisionBox->SetHiddenInGame(false, true);  // Oyun sırasında ve editörde görünür


	const ConstructorHelpers::FObjectFinder<UStaticMesh> SoldierMesh(TEXT("/Game/Maps/_GENERATED/FurkanBULBUL/SoldierM"));
	if (SoldierMesh.Succeeded())
	{
		SoldiersMesh->SetSimulatePhysics(true);
		SoldiersMesh->SetCollisionProfileName(TEXT("Pawn"));
		SoldiersMesh->SetStaticMesh(SoldierMesh.Object);
	}
	else
	{
		UE_LOG(LogTemp,Warning,TEXT("Unsuccesfull attempt"))
	}
}
void AAI_Soldiers::BeginPlay()
{
	Super::BeginPlay();

	if (APlayerController* PlayerController = UGameplayStatics::GetPlayerController(this, 0))
	{
		EnableInput(PlayerController);
		SpawnSoldierInstances(GetActorLocation());
	}
	
}
void AAI_Soldiers::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
void AAI_Soldiers::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void AAI_Soldiers::SpawnSoldierInstances(const FVector& SpawnLocation)
{
	SoldiersMesh->ClearInstances();
    if (URTSGameInstance* GameInstance = Cast<URTSGameInstance>(UGameplayStatics::GetGameInstance(GetWorld())))
    {
        PackSize = GameInstance->GetArmySizes();

        const FVector RandomLocation(0.0f, 0.0f, 0.0f);
        const int32 SideCount = FMath::Sqrt(PackSize);
        const float TotalWidth = (SideCount - 1) * Spacing;
        const float TotalHeight = (SideCount - 1) * Spacing;
        const FVector CollisionBoxSize(TotalWidth, TotalHeight,20); // SoldierHeight, askerin yüksekliği
        const FVector CollisionBoxCenter = RandomLocation + FVector(TotalWidth / 2, TotalHeight / 2, 20.f/2);
    	
		SoldiersCollisionBox->SetBoxExtent(CollisionBoxSize / 2); // BoxExtent, collision box'un yarısı kadar olmalı
		SoldiersCollisionBox->SetWorldLocation(CollisionBoxCenter);
        const FVector NewBoxExtent = CollisionBoxSize; // Örnek olarak boyutları 1.5 katına çıkar
		SoldiersCollisionBox->SetBoxExtent(NewBoxExtent);
		
		FVector TotalLocation = FVector::ZeroVector;
		int32 SoldierCount = 0;

		for (int32 Row = 0; Row < SideCount; ++Row)
		{
			for (int32 Column = 0; Column < SideCount; ++Column)
			{
				FVector InstancedLocation = FVector(RandomLocation.X + Row * Spacing, RandomLocation.Y + Column * Spacing, 0.f);
				FTransform InstanceTransform = FTransform(InstancedLocation);
				InstanceIndex = SoldiersMesh->AddInstance(InstanceTransform);
            
				TotalLocation += InstancedLocation;  // Toplam konumu güncelle
				SoldierCount++;  // Asker sayısını güncelle
				
			}
		}
		FVector AverageLocation = TotalLocation / SoldierCount;  // Ortalama konumu hesapla
    	SoldiersCollisionBox->SetWorldLocation(SpawnLocation + FVector(TotalWidth / 2, TotalHeight / 2, CollisionBoxSize.Z / 2));

        const FVector CollisionBoxWorldLocation = SoldiersCollisionBox->GetComponentLocation();
        const FVector MeshWorldLocation = SoldiersMesh->GetComponentLocation();
		UE_LOG(LogTemp, Warning, TEXT("CollisionBox World Location: %s"), *CollisionBoxWorldLocation.ToString());
		UE_LOG(LogTemp, Warning, TEXT("Mesh World Location: %s"), *MeshWorldLocation.ToString());
	}
	
}