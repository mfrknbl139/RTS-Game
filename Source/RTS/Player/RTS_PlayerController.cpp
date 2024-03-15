/* Copy Rights
 * 
 * 
 */

#include "RTS_PlayerController.h"
#include "RTS/AI/AI_Soldiers.h"
#include "RTS/GridActor.h"
#include "Kismet/GameplayStatics.h"
#include "RTS/BaseUnitSpawner.h"

ARTS_PlayerController::ARTS_PlayerController()
{
	// Initialize the SoldierPack pointer
	SoldierPack = nullptr;
	FInputModeGameAndUI InputMode;
	InputMode.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
	InputMode.SetHideCursorDuringCapture(false);
	SetInputMode(InputMode);
	bShowMouseCursor = true;
	
}

AAI_Soldiers* ARTS_PlayerController::GetSoldiersPack() const
{
	return SoldierPack;
}

void ARTS_PlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
	//InputComponent->BindAction("SpawnSoldiers", IE_Pressed, this, &ARTS_PlayerController::OnSpawnSoldiers);
	InputComponent->BindAction("LeftMouseClick", IE_Pressed, this, &ARTS_PlayerController::OnLeftMouseClick);
//	InputComponent->BindAction("SpawnActor", IE_Pressed, this, &ARTS_PlayerController::OnLeftMouseClick);
}
void ARTS_PlayerController::SomeFunctionToSetSoldierPack()
{
	// Logic to find and set your soldier pack
	// For example, you might find the soldier pack in the level and set it
	SoldierPack = Cast<AAI_Soldiers>(UGameplayStatics::GetActorOfClass(GetWorld(), AAI_Soldiers::StaticClass()));
}

void ARTS_PlayerController::SetSoldierPack(AAI_Soldiers* NewSoldierPack)
{
	SoldierPack = NewSoldierPack;
}
void ARTS_PlayerController::OnLeftMouseClick()
{
	FHitResult HitResult;
	if (GetHitResultUnderCursor(ECollisionChannel::ECC_Visibility, false, HitResult))
	{
		FVector ClickedLocation = HitResult.ImpactPoint;

		if (BaseUnitSpawnerClass != nullptr)
		{
			UE_LOG(LogTemp, Warning, TEXT("Attempting to spawn at location: %s"), *ClickedLocation.ToString());

			FActorSpawnParameters SpawnParams;
			ABaseUnitSpawner* SpawnedActor = GetWorld()->SpawnActor<ABaseUnitSpawner>(BaseUnitSpawnerClass, ClickedLocation, FRotator::ZeroRotator, SpawnParams);

			if (SpawnedActor)
			{
				UE_LOG(LogTemp, Warning, TEXT("Actor spawned successfully at %s."), *SpawnedActor->GetActorLocation().ToString());
				// Optionally, call a function on SpawnedActor here
			}
			else
			{
				UE_LOG(LogTemp, Warning, TEXT("Failed to spawn actor."));
			}
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("BaseUnitSpawnerClass not set. Please assign a class to spawn."));
		}
	}
}

void ARTS_PlayerController::HandleLeftClick()
{
	FHitResult HitResult;
	//GetHitResultUnderCursor(ECollisionChannel::ECC_Visibility, false, HitResult); // You might adjust the collision channel based on your needs
	if (GetHitResultUnderCursor(ECollisionChannel::ECC_Visibility, false, HitResult))
	{
		UE_LOG(LogTemp, Warning, TEXT("Hit: %s"), *HitResult.ImpactPoint.ToString());
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("No hit detected."));
	}
	if (HitResult.bBlockingHit)
	{
		FVector LocalSpawnLocation = HitResult.ImpactPoint;
		FRotator LocalSpawnRotation = FRotator::ZeroRotator; // Adjust if needed

		FActorSpawnParameters SpawnParams;
		SpawnParams.Owner = this;
		SpawnParams.Instigator = GetPawn();

		// Replace AYourActorClass with your actual actor class
		ABaseUnitSpawner* SpawnedActor = GetWorld()->SpawnActor<ABaseUnitSpawner>(ABaseUnitSpawner::StaticClass(), SpawnLocation, LocalSpawnRotation, SpawnParams);

		if (SpawnedActor)
		{
			// Optionally do something with the spawned actor
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

	FVector NewSpawnLocation = GridActor->GetRandomUnoccupiedGridLocation();
	if (NewSpawnLocation == FVector(-1, -1, -1))
	{
		//UE_LOG(LogTemp, Warning, TEXT("No empty location available for spawning."));
		return;
	}

	FActorSpawnParameters SpawnParams;
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

	if (BPAI_Soldiers) // Check if the Blueprint class is set
	{
		AAI_Soldiers* NewSoldiersActor = GetWorld()->SpawnActor<AAI_Soldiers>(BPAI_Soldiers, NewSpawnLocation, FRotator::ZeroRotator, SpawnParams);
		if (NewSoldiersActor)
		{
			
			UE_LOG(LogTemp, Warning, TEXT("Blueprint soldiers spawned at location: X: %f, Y: %f"), NewSpawnLocation.X, NewSpawnLocation.Y);
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("Failed to spawn blueprint soldiers."));
		}
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Blueprint class not set."));


	}
}

