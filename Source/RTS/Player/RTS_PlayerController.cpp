/* Copy Rights
 * 
 * 
 */

#include "RTS_PlayerController.h"
#include "RTS/AI/AI_Soldiers.h"
#include "RTS/GridActor.h"
#include "Kismet/GameplayStatics.h"

ARTS_PlayerController::ARTS_PlayerController()
{
	// Initialize the SoldierPack pointer
	SoldierPack = nullptr;
}


void ARTS_PlayerController::SomeFunctionToSetSoldierPack()
{
	// Logic to find and set your soldier pack
	// For example, you might find the soldier pack in the level and set it
	SoldierPack = Cast<AAI_Soldiers>(UGameplayStatics::GetActorOfClass(GetWorld(), AAI_Soldiers::StaticClass()));
}

void ARTS_PlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
	InputComponent->BindAction("SpawnSoldiers", IE_Pressed, this, &ARTS_PlayerController::OnSpawnSoldiers);
	InputComponent->BindAction("LeftMouseClick", IE_Pressed, this, &ARTS_PlayerController::OnLeftMouseClick); //input action needs to be bound.
	
}
AAI_Soldiers* ARTS_PlayerController::GetSoldiersPack() const
{
	return SoldierPack;
}
void ARTS_PlayerController::SetSoldierPack(AAI_Soldiers* NewSoldierPack)
{
	SoldierPack = NewSoldierPack;
}
void ARTS_PlayerController::OnLeftMouseClick()
{
	FVector ClickedLocation;
	FHitResult HitResult;
	if (GetHitResultUnderCursor(ECollisionChannel::ECC_Visibility, false, HitResult))
	{
		ClickedLocation = HitResult.Location;

		// Assuming you have a reference to your soldier pack actor
		if (AAI_Soldiers* SoldiersPack = GetSoldiersPack())
		{
			SoldiersPack->MoveToLocation(ClickedLocation);
		}
	}
}

void ARTS_PlayerController::OnSpawnSoldiers()
{
	AGridActor* GridActor = Cast<AGridActor>(UGameplayStatics::GetActorOfClass(GetWorld(), AGridActor::StaticClass()));
	if (!GridActor)
	{
		UE_LOG(LogTemp, Warning, TEXT("GridActor not found."));
		return;
	}

	FVector NewSpawnLocation = GridActor->GetRandomUnoccupiedGridLocation(); // Yeni spawn konumu

	if (NewSpawnLocation == FVector(-1, -1, -1)) // Konum geçerli mi kontrol et
	{
		UE_LOG(LogTemp, Warning, TEXT("No empty location available for spawning."));
		return;
	}

	// Mark the location if it is in used
	GridActor->SetLocationOccupied(NewSpawnLocation.X, NewSpawnLocation.Y, true);

	FActorSpawnParameters SpawnParams;
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;
    
	// Spawn actor to a random location
	AAI_Soldiers* NewSoldiersActor = GetWorld()->SpawnActor<AAI_Soldiers>(AAI_Soldiers::StaticClass(), NewSpawnLocation, SpawnRotator, SpawnParams);
	if (NewSoldiersActor)
	{
		NewSoldiersActor->SpawnSoldierInstances(NewSpawnLocation);
		UE_LOG(LogTemp, Warning, TEXT("Soldiers spawned at location: X: %f, Y: %f"), NewSpawnLocation.X, NewSpawnLocation.Y);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Failed to spawn soldiers."));
	}
}
	

