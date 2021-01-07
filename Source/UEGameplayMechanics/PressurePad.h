// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PressurePad.generated.h"

UENUM(BlueprintType)
enum class EActiveStatus : uint8
{
	EAS_Weight		UMETA(DisplayName = "Weight"),
	EAS_KeyItem		UMETA(DisplayName = "KeyItem"),
	EAS_Both		UMETA(DisplayName = "Both"),

	EAS_MAX			UMETA(DisplayName = "DefaultMax")
};

UCLASS()
class UEGAMEPLAYMECHANICS_API APressurePad : public AActor
{
	GENERATED_BODY()
	
public:	
	APressurePad();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pressure Pad")
	class ATriggerDoor* TriggerDoor;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Pressure Pad")
	class UBoxComponent* TriggerBox;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Pressure Pad")
	class UStaticMeshComponent* ScalePad;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pressure Pad | Item | ParticleSystem")
	class UParticleSystem* PassEffect;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pressure Pad | Item | Sound")
	class USoundCue* PassSound;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pressure Pad | Item")
	EActiveStatus ActiveStatus;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pressure Pad | Item", meta = (EditCondition = "ActiveStatus == EActiveStatus::EAS_Weight || ActiveStatus == EActiveStatus::EAS_Both "))
	float MinWeightToTrigger;

	UPROPERTY(EditAnywhere, blueprintReadWrite, Category = "Pressure Pad | Item", meta = (EditCondition = "ActiveStatus == EActiveStatus::EAS_Weight || ActiveStatus == EActiveStatus::EAS_Both"))
	float MaxWeightToTrigger;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pressure Pad | Item", meta = (EditCondition = "ActiveStatus == EActiveStatus::EAS_KeyItem || ActiveStatus == EActiveStatus::EAS_Both"))
	class AItem* KeyItem;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Pressure Pad | Item")
	TMap<AItem*, float> ItemOnPadList;

	UPROPERTY(VisibleAnywhere)
	float CurrentAllItemsWeight;

protected:
	virtual void BeginPlay() override;

public:
	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	UFUNCTION(BlueprintImplementableEvent, Category = "Pressure Pad")
	void LowerScalePad();

	UFUNCTION(BlueprintImplementableEvent, Category = "Pressure Pad")
	void RaiseScalePad();

	UFUNCTION(BlueprintCallable, Category = "Pressure Pad")
	void UpdateScalePadLocation(FVector Location);

private:
	FVector InitialDoorLocation;
	FVector InitialScalePadLocation;
	void TriggerPass();
	void BackToUnTrigger(AItem* Item);
	void CheckKeyItem(AItem* Item);
	void CheckWeight(AItem* Item);
	bool bItemCorrect;
	bool bWeightCorrect;
	bool CheckTotalWeight();
};
