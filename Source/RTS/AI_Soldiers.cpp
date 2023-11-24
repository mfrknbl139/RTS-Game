#include "AI_Soldiers.h"

#include "AISoldiersController.h"
#include "Components/InstancedStaticMeshComponent.h"
#include "UObject/ConstructorHelpers.h"
#include "RTSGameInstance.h"
#include "Kismet/GameplayStatics.h"

AAI_Soldiers::AAI_Soldiers()
{
	PrimaryActorTick.bCanEverTick = false;

	AIControllerClass=AAISoldiersController::StaticClass();//Controller class ataması.
	
	SoldiersMesh = CreateDefaultSubobject<UInstancedStaticMeshComponent>(TEXT("SoldiersMesh"));
	RootComponent=SoldiersMesh;
	
	ConstructorHelpers::FObjectFinder<UStaticMesh> SoldierMesh(TEXT("/Game/Maps/_GENERATED/FurkanBULBUL/SoldierM"));
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
	SpawnSoldierInstances();
	APlayerController* PlayerController = UGameplayStatics::GetPlayerController(this, 0);
	if (PlayerController)
	{
		EnableInput(PlayerController);
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

void AAI_Soldiers::SpawnSoldierInstances()
{
	SoldiersMesh->ClearInstances();
	if (URTSGameInstance* GameInstance = Cast<URTSGameInstance>(UGameplayStatics::GetGameInstance(GetWorld())))
	{
		PackSize = GameInstance->GetArmySizes();
		int16 InstanceIndex;
		float Spacing = 100.0f;
		FVector RandomLocation;

		RandomLocation.X = FMath::RandRange(10.0f, PackSize *100.0f);
		RandomLocation.Y = FMath::RandRange(10.0f, PackSize *100.0f);

		for (uint32 Row = 0; Row < PackSize; ++Row)
		{
			for (uint32 Column = 0; Column < PackSize; ++Column)
			{
				FVector InstancedLocation = FVector(RandomLocation.X + Row * Spacing, RandomLocation.Y + Column * Spacing, 0.f);
				FTransform InstanceTransform = FTransform(InstancedLocation);
				InstanceIndex = SoldiersMesh->AddInstance(InstanceTransform);
			}
		}
	}
}

