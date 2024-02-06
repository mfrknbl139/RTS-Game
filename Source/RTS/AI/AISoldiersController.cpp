// Fill out your copyright notice in the Description page of Project Settings.


#include "AISoldiersController.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "UObject/ConstructorHelpers.h"


AAISoldiersController::AAISoldiersController()
{
	static ConstructorHelpers::FObjectFinder<UBehaviorTree>Obj(TEXT("/Game/AI/BT_Soldiers.BT_Soldiers"));
	if (Obj.Succeeded())
	{
		BehaviorTree=Obj.Object;
	}
}
/*
 *	Behavior Tree Component !
 * 
 */
void AAISoldiersController::BeginPlay()
{
	Super::BeginPlay();
	if (BehaviorTree)
	{
		RunBehaviorTree(BehaviorTree);
		if (BehaviorTree)
		{
			UE_LOG(LogTemp,Warning,TEXT("Furkan Working: "))
		}
	
		GetBlackboardComponent()->SetValueAsVector("TargetLocation", FVector(0.0f, 0.0f, 0.0f)); // Example initial value
	}
	if (GetBlackboardComponent())
	{
		FVector RandomLocation ; // Calculate or retrieve this location based on your game logic
		GetBlackboardComponent()->SetValueAsVector("RandomPath", RandomLocation);

		// Log to confirm
		FVector LoggedLocation = GetBlackboardComponent()->GetValueAsVector("RandomPath");
		UE_LOG(LogTemp, Warning, TEXT("Random Path Location: %s"), *LoggedLocation.ToString());
	}
	if (GetBlackboardComponent())
	{
		GetBlackboardComponent()->SetValueAsObject("SelfActor", this);

		// Log to confirm
		AActor* LoggedActor = Cast<AActor>(GetBlackboardComponent()->GetValueAsObject("SelfActor"));
		if (LoggedActor)
		{
			UE_LOG(LogTemp, Warning, TEXT("Self Actor: %s"), *LoggedActor->GetName());
		}
	}


}
