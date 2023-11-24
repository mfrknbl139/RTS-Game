// Fill out your copyright notice in the Description page of Project Settings.


#include "AISoldiersController.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"


AAISoldiersController::AAISoldiersController()
{
	static ConstructorHelpers::FObjectFinder<UBehaviorTree>Obj(TEXT("/Game/AI/BT_Soldiers.BT_Soldiers"));
	if (Obj.Succeeded())
	{
		BehaviorTree=Obj.Object;
	}
}

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
}
