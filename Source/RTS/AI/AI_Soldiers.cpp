#include "AI_Soldiers.h"
#include "AISoldiersController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "UObject/ConstructorHelpers.h"
#include "RTS/RTSGameInstance.h"
#include "Kismet/GameplayStatics.h"



AAI_Soldiers::AAI_Soldiers()
{

	PrimaryActorTick.bCanEverTick = false;
	AIControllerClass=AAISoldiersController::StaticClass();//Controller class ataması.
	SoldiersSkeletalMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("SoldiersSkeletalMesh"));
	RootComponent = SoldiersSkeletalMesh;
	
	// SoldiersCollisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("SoldiersCollisionBox"));
	// SoldiersCollisionBox->SetupAttachment(RootComponent);
}

void AAI_Soldiers::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AAI_Soldiers::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
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

/*
 *
 * Move pack to clicked location. Has not yet been initiliazed
 *
 */
void AAI_Soldiers::MoveToLocation(const FVector& TargetLocation)
{
	AAISoldiersController* AIController = Cast<AAISoldiersController>(GetController());
	if (AIController)
	{
		AIController->GetBlackboardComponent()->SetValueAsVector("TargetLocation", TargetLocation);
	}
}

/*
 *
 *	Spawns soldiers meshes square as pack
 * 
 */

void AAI_Soldiers::SpawnSoldierInstances(const FVector& SpawnLocation)
{
	SoldiersMesh->ClearInstances();
    if (URTSGameInstance* GameInstance = Cast<URTSGameInstance>(UGameplayStatics::GetGameInstance(GetWorld())))
    {
        PackSize = GameInstance->GetArmySizes();
        FVector RandomLocation(0.0f, 0.0f, 0.0f);
        int32 SideCount = FMath::Sqrt(PackSize);
        float TotalWidth = (SideCount - 1) * Spacing;
        float TotalHeight = (SideCount - 1) * Spacing;
        FVector CollisionBoxSize(TotalWidth, TotalHeight,20); // SoldierHeight, askerin yüksekliği
        FVector CollisionBoxCenter = RandomLocation + FVector(TotalWidth / 2, TotalHeight / 2, 20.f/2);
    	
		SoldiersCollisionBox->SetBoxExtent(CollisionBoxSize / 2); // BoxExtent, collision box'un yarısı kadar olmalı
		SoldiersCollisionBox->SetWorldLocation(CollisionBoxCenter);
        FVector NewBoxExtent = CollisionBoxSize; // Örnek olarak boyutları 1.5 katına çıkar
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