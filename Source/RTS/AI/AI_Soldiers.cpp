#include "AI_Soldiers.h"
#include "AISoldiersController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Components/BoxComponent.h"
#include "UObject/ConstructorHelpers.h"
#include "RTS/RTSGameInstance.h"
#include "Kismet/GameplayStatics.h"

AAI_Soldiers::AAI_Soldiers()
{
	PrimaryActorTick.bCanEverTick = false;
	AIControllerClass = AAISoldiersController::StaticClass();

	// Initialize the collision box
	SoldiersCollisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("SoldiersCollisionBox"));
	RootComponent = SoldiersCollisionBox;
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
	if (URTSGameInstance* GameInstance = Cast<URTSGameInstance>(UGameplayStatics::GetGameInstance(GetWorld())))
	{
		PackSize = GameInstance->GetArmySizes();
		FVector RandomLocation(0.0f, 0.0f, 0.0f);
		SideCount = FMath::Sqrt(PackSize);
		TotalWidth = (SideCount - 1) * 100.0f;
		TotalHeight = (SideCount - 1) * 100.0f;

		FVector CollisionBoxSize(TotalWidth, TotalHeight, 20.0f);
		CollisionBoxCenter = SpawnLocation + FVector(TotalWidth / 2, TotalHeight / 2, 20.0f / 2);

		SoldiersCollisionBox->SetBoxExtent(CollisionBoxSize / 2);
		SoldiersCollisionBox->SetWorldLocation(CollisionBoxCenter);

		


		
	}
}

void AAI_Soldiers::LogCollisionAndMeshLocations()
{
	UE_LOG(LogTemp,Warning,TEXT("warning"))
}
