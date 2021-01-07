// Fill out your copyright notice in the Description page of Project Settings.


#include "AIBTService_CheckForPlayer.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/Blackboard/BlackboardKeyAllTypes.h"
#include "../UEGameplayMechanicsCharacter.h"
#include "EnemyAICharacter.h"
#include "EnemyAIController.h"

UAIBTService_CheckForPlayer::UAIBTService_CheckForPlayer()
{
	bCreateNodeInstance = true;
}

void UAIBTService_CheckForPlayer::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	AEnemyAIController* EnemyAICon = Cast<AEnemyAIController>(OwnerComp.GetAIOwner());

	if (EnemyAICon)
	{
		AUEGameplayMechanicsCharacter* Player = Cast<AUEGameplayMechanicsCharacter>(GetWorld()->GetFirstPlayerController()->GetPawn());

		/*if (Player)
		{
			OwnerComp.GetBlackboardComponent()->SetValue<UBlackboardKeyType_Object>(EnemyAICon->EnemyKeyID, Player);
			GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Green, "Player is here!");
		}*/
	}
}
