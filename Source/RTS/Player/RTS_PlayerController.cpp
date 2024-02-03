#include "RTS_PlayerController.h"

#include "RTS/AI/AI_Soldiers.h"
#include "RTS/GridActor.h"
#include "RTS/RTSGameInstance.h"
#include "Kismet/GameplayStatics.h"

void ARTS_PlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
	InputComponent->BindAction("SpawnSoldiers", IE_Pressed, this, &ARTS_PlayerController::OnSpawnSoldiers);
	
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

	// İlgili konumu işgal edilmiş olarak işaretle
	GridActor->SetLocationOccupied(NewSpawnLocation.X, NewSpawnLocation.Y, true);

	FActorSpawnParameters SpawnParams;
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;
    
	// Actor'ü rastgele seçilen konumda spawn et
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
	


