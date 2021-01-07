// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "EnemyAICharacter.generated.h"

UCLASS()
class UEGAMEPLAYMECHANICS_API AEnemyAICharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AEnemyAICharacter();

	UPROPERTY(VisibleAnywhere, Category = "AI")
	class UPawnSensingComponent* PawnSensingComp;

	UPROPERTY(EditAnywhere, Category = "AI")
	class UBehaviorTree* BotBehavior;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
	float SuspectionTime;

	/* How fast the actor will rotate to the location when hearing something*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
	float InterpSpeed;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual void Tick(float DeltaTime) override;


	UFUNCTION(BlueprintCallable, Category = "AI")
	FRotator GetLookAtRotation();

private:
	FRotator OriginalRotation;
	FTimerHandle ResetOrientationTimerHandle;
	FVector SuspectLocation;
	bool bIsSuspecting;
	bool bShouldResetOrientation;
	UFUNCTION()
	void OnPlayerCaught(APawn* Pawn);

	UFUNCTION()
	void OnSuspection(APawn* Pawn, const FVector& Location, float Volume);

	UFUNCTION()
	void ResetOrientation();

};
