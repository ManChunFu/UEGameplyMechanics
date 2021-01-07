// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "AIBTService_CheckForPlayer.generated.h"

/**
 * 
 */
UCLASS()
class UEGAMEPLAYMECHANICS_API UAIBTService_CheckForPlayer : public UBTService
{
	GENERATED_BODY()
	
public:
	UAIBTService_CheckForPlayer();

public:
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
};
