#include "RTS_PlayerController.h"
#include "AI_Soldiers.h"
#include "GridActor.h"
#include "Kismet/GameplayStatics.h"

void ARTS_PlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
	InputComponent->BindAction("SpawnSoldiers", IE_Pressed, this, &ARTS_PlayerController::OnSpawnSoldiers);
}

void ARTS_PlayerController::OnSpawnSoldiers()
{
	AGridActor* GridActor = Cast<AGridActor>(UGameplayStatics::GetActorOfClass(GetWorld(), AGridActor::StaticClass()));
	if (GridActor)
	{
		SpawnLocation = GridActor->GetRandomUnoccupiedGridLocation();
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("GridActor not found."));
		return;
	}

	FActorSpawnParameters SpawnParams;
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

	AAI_Soldiers* NewSoldiersActor = GetWorld()->SpawnActor<AAI_Soldiers>(AAI_Soldiers::StaticClass(), SpawnLocation, SpawnRotator, SpawnParams);
	if (NewSoldiersActor)
	{
		NewSoldiersActor->SpawnSoldierInstances();
		UE_LOG(LogTemp, Warning, TEXT("Soldiers spawned."));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Failed to spawn soldiers."));
	}
	
}
/*
bool ARTS_PlayerController::IsLocationFree(const FVector& NewLocation, float RequiredRadius)
{
	for (const FVector& OccupiedLocation:OccupiedLocations)
	{
		if (FVector::DistSquared(OccupiedLocation,NewLocation)<FMath::Square(RequiredRadius))
		{
			return false;
		}
	}
	return true;
}
*/
