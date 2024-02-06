// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "BTTask_MoveRandomPath.generated.h"

/*
 * 
 */
UCLASS()
class RTS_API UBTTask_MoveRandomPath : public UBTTask_BlackboardBase
{
	GENERATED_BODY()

public:
	UBTTask_MoveRandomPath(const FObjectInitializer& ObjectInitializer);

	
private:
	EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory);

   
};
