// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "QuickSand.generated.h"

UCLASS()
class UEGAMEPLAYMECHANICS_API AQuickSand : public AActor
{
	GENERATED_BODY()
	
public:	
	AQuickSand();

protected:
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, Category = "SinkingActor")
	class UStaticMeshComponent* SurfaceComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "SinkingActor")
	UStaticMeshComponent* MoveableComp;

	UPROPERTY(VisibleAnywhere, Category = "SinkingActor")
	class UBoxComponent* DeadZoneComp;

	/* How fast to sink down, 0 = No movement */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SinkingActor")
	float SinkingRate = 0.01f;

	/* How many CM to sink down per time */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SinkingActor")
	float SinkingLength = 5.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SinkingActor")
	float FirstTimeDelay = 3.0f;

	UFUNCTION(BlueprintCallable)
	void OverlapMoveableComp(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION(BlueprintCallable)
	void EndOverlapMoveableComp(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	UFUNCTION(BlueprintCallable)
	void OverlapDeadZoneComp(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	FTimerHandle MoveCompTimerHandle;
	FTimerHandle MoveBackCompTimerHandle;

	UFUNCTION(BlueprintCallable)
	void SinkDown();

	UFUNCTION(BlueprintCallable)
	void SetBackToOriginalLocation();

private:
	TArray<AActor*> OverlappingActors;
	int32 Counter = 0;
	FVector OriginalLocation;
	float DefaultFirstTimeDelay;
};
