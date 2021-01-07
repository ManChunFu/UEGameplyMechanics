// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyAIController.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/Blackboard/BlackboardKeyAllTypes.h"
#include "EnemyAICharacter.h"
#include "Kismet/GameplayStatics.h"



AEnemyAIController::AEnemyAIController()
{
	// Initialise the blackboard and behavior tree
	BlackboardComp = CreateDefaultSubobject<UBlackboardComponent>(TEXT("BlackboardComp"));
	BehaviorComp = CreateDefaultSubobject<UBehaviorTreeComponent>(TEXT("BehaviorComp"));

	// Initialise the blackboard keys
	// name of the key in the blackboard
	PlayerLocationKey = "Target";
	LocationKey = "LocationToMove";

	// Initialise the current patrol point
	CurrentPatrolPoint = 0;
}

void AEnemyAIController::SetPawn(APawn* InPawn)
{
	Super::SetPawn(InPawn);

	// Get reference to the character itself
	AEnemyAICharacter* EnemyAICharacter = Cast<AEnemyAICharacter>(InPawn);

	if (EnemyAICharacter)
	{
		if (EnemyAICharacter->BotBehavior->BlackboardAsset)
		{
			BlackboardComp->InitializeBlackboard(*EnemyAICharacter->BotBehavior->BlackboardAsset);
		}

		//EnemyKeyID = BlackboardComp->GetKeyID("Target");

		// Populate patrol point array
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), AEnemyAIController::StaticClass(), PatrolPoints);

		// Run behavior tree
		BehaviorComp->StartTree(*EnemyAICharacter->BotBehavior);
	}
}

void AEnemyAIController::SetPlayerCaught(APawn* PlayerPawn)
{
	if (BlackboardComp)
	{
		BlackboardComp->SetValueAsObject(PlayerLocationKey, PlayerPawn);
	}
}
