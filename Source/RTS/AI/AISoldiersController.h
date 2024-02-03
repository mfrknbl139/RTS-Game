// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "BehaviorTree/BehaviorTree.h"
#include "AISoldiersController.generated.h"

/**
 * 
 */
UCLASS()
class RTS_API AAISoldiersController : public AAIController
{
	GENERATED_BODY()

public:
	AAISoldiersController();
protected:
	virtual void BeginPlay() override;
private:
	UPROPERTY()
	UBehaviorTree* BehaviorTree;
	
};
