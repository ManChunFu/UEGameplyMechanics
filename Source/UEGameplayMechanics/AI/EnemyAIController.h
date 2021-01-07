// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "EnemyAIController.generated.h"

/**
 * 
 */
UCLASS()
class UEGAMEPLAYMECHANICS_API AEnemyAIController : public AAIController
{
	GENERATED_BODY()

public:
	AEnemyAIController();

	UPROPERTY(transient)
	class UBlackboardComponent* BlackboardComp;

	UPROPERTY(transient)
	class UBehaviorTreeComponent* BehaviorComp;

	// Blackboard Keys
	UPROPERTY(EditDefaultsOnly, Category = "AI")
	FName LocationKey; // Location(point) for AI to move to 

	UPROPERTY(EditDefaultsOnly, Category = "AI")
	FName PlayerLocationKey; // Refernce to the player's location

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
	TArray<class AActor*> PatrolPoints;

	UPROPERTY(VisibleAnywhere, Category = "AI")
	int32 CurrentPatrolPoint;

public:
	virtual void SetPawn(APawn* InPawn) override;

	void SetPlayerCaught(APawn* Pawn);

	FORCEINLINE UBlackboardComponent* GetBlackboardComponent() const { return BlackboardComp; }
	FORCEINLINE TArray<AActor*> GetPatrolPoints() const { return PatrolPoints; }

	//uint8 EnemyKeyID;
};
