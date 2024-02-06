// Fill out your copyright notice in the Description page of Project Settings.


//#include "BTTask_MoveRandomPath.h"
#include "BTTask_MoveRandomPath.h"

#include "BehaviorTree/BehaviorTreeTypes.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AIController.h"
#include "NavigationSystem.h"
#include "AI_Soldiers.h"
#include "NavigationSystem.h"

UBTTask_MoveRandomPath::UBTTask_MoveRandomPath(const FObjectInitializer& ObjectInitializer): Super(ObjectInitializer)
{
	NodeName = "Random Patrol";
}


//Navigation Bound has to be placed in Level
EBTNodeResult::Type UBTTask_MoveRandomPath::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AAIController* AICon = OwnerComp.GetAIOwner();
	if (AICon)
	{
		// Get the world and navigation system
		UWorld* World = AICon->GetWorld();
		UNavigationSystemV1* NavSys = FNavigationSystem::GetCurrent<UNavigationSystemV1>(World);

		auto NavSystem = UNavigationSystemV1::GetCurrent(GetWorld());
		if (NavSystem)
		{
			FVector MyLocation = OwnerComp.GetAIOwner()->GetPawn()->GetActorLocation();
			FNavLocation RandomLocation;

			if (NavSystem->GetRandomPointInNavigableRadius(MyLocation, 1000.0f, RandomLocation))
			{
				// Do something with RandomLocation
			}
		}
		return EBTNodeResult::Succeeded;
	}

	return EBTNodeResult::Failed;
}

