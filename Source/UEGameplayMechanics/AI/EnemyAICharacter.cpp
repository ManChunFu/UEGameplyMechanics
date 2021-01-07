// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyAICharacter.h"
#include "BehaviorTree/BehaviorTree.h"
#include "Perception/PawnSensingComponent.h"
#include "EnemyAIController.h"
#include "DrawDebugHelpers.h"

// Sets default values
AEnemyAICharacter::AEnemyAICharacter()
{
	PawnSensingComp = CreateDefaultSubobject<UPawnSensingComponent>(TEXT("PawnSensingComp"));
	PawnSensingComp->SetPeripheralVisionAngle(90.0f);

	SuspectionTime = 3.0f;
	InterpSpeed = 15.0f;
	bIsSuspecting = false;
}

// Called when the game starts or when spawned
void AEnemyAICharacter::BeginPlay()
{
	Super::BeginPlay();

	if (PawnSensingComp)
	{
		PawnSensingComp->OnSeePawn.AddDynamic(this, &AEnemyAICharacter::OnPlayerCaught);
		PawnSensingComp->OnHearNoise.AddDynamic(this, &AEnemyAICharacter::OnSuspection);
	}

	OriginalRotation = GetActorRotation();
	
}

// Called to bind functionality to input
void AEnemyAICharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AEnemyAICharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (bIsSuspecting)
	{
		FRotator InterpRotation = FMath::RInterpTo(GetActorRotation(), GetLookAtRotation(), DeltaTime, InterpSpeed);
		SetActorRotation(InterpRotation);
	}
	if (bShouldResetOrientation)
	{
		FRotator InterpRotation = FMath::RInterpTo(GetActorRotation(), OriginalRotation, DeltaTime, InterpSpeed);
		SetActorRotation(InterpRotation);
		if (GetActorRotation() == OriginalRotation)
		{
			bIsSuspecting = false;
			bShouldResetOrientation = false;
		}
	}
	
}

FRotator AEnemyAICharacter::GetLookAtRotation()
{
	FVector Direction = SuspectLocation - GetActorLocation();
	Direction.Normalize();

	FRotator LookAtRotation = FRotationMatrix::MakeFromX(Direction).Rotator();
	LookAtRotation.Pitch = 0.0f;
	LookAtRotation.Roll = 0.0f;

	return LookAtRotation;
}

void AEnemyAICharacter::OnPlayerCaught(APawn* Pawn)
{
	if (Pawn == nullptr)
	{
		return;
	}

	AEnemyAIController* EnemyAIController = Cast<AEnemyAIController>(GetController());

	if (EnemyAIController && PawnSensingComp->HasLineOfSightTo(Pawn))
	{
		GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Green, "Player is here!");
		EnemyAIController->SetPlayerCaught(Pawn);
		bIsSuspecting = false;
		bShouldResetOrientation = false;
	}
	else 
	{
		GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Green, "Not here!");

	}
}

void AEnemyAICharacter::OnSuspection(APawn* Pawn, const FVector& Location, float Volume)
{
	GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Cyan, "I hear something!");
	DrawDebugSphere(GetWorld(), Location, 32.0f, 12, FColor::Yellow, false, 2.0f);

	SuspectLocation = Location;
	bIsSuspecting = true;

	GetWorldTimerManager().ClearTimer(ResetOrientationTimerHandle);
	GetWorldTimerManager().SetTimer(ResetOrientationTimerHandle, this, &AEnemyAICharacter::ResetOrientation, SuspectionTime, false);
}

void AEnemyAICharacter::ResetOrientation()
{
	bShouldResetOrientation = true;
}


