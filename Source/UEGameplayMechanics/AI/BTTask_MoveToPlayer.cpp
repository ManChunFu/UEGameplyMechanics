// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_MoveToPlayer.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/Blackboard/BlackboardKeyAllTypes.h"
#include "EnemyAICharacter.h"
#include "EnemyAIController.h"
#include "../UEGameplayMechanicsCharacter.h"


EBTNodeResult::Type UBTTask_MoveToPlayer::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AEnemyAIController* EnemyAICon = Cast<AEnemyAIController>(OwnerComp.GetAIOwner());
	//Store value from key "Target" on BlackBoard
	//AUEGameplayMechanicsCharacter* Player = Cast<AUEGameplayMechanicsCharacter>(OwnerComp.GetBlackboardComponent()->GetValue<UBlackboardKeyType_Object>(EnemyAICon->EnemyKeyID));
	
	//if (Player)
	//{
	//	EnemyAICon->MoveToActor(Player, 5.0f, true, true, true, 0, true);
	//	return EBTNodeResult::Succeeded;
	//}
	//else
	//{
	//	return EBTNodeResult::Failed;
	//}
	return EBTNodeResult::Failed;
}