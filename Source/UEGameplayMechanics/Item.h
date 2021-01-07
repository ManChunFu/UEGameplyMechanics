// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Item.generated.h"

UCLASS()
class UEGAMEPLAYMECHANICS_API AItem : public AActor
{
	GENERATED_BODY()
	
public:
	AItem();

	/** Base shape collision */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Item | Collision")
	class USphereComponent* CollisionVolume;

	/*** Base Mesh Component */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Item | Mesh")
	class UStaticMeshComponent* ObjectMesh;

	/** Base pariticle effect with object */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item | Particles | Idle")
	class UParticleSystemComponent* IdleParticlesComponent;

	/** Base particle effect when overlaping the object*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item | Particles | Overlap")
	class UParticleSystem* OverlapParticles;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item | Sound")
	class USoundCue* OverlapSound;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item | Weight")
	bool bOverrideMassWeight;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item | Weight", meta = (EditCondition = "bOverrideMassWeight"))
	float MassWeight;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item | Other")
	bool bDefaultRotationOnPickup;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item | Other")
	bool bOffCenterHoldingPos;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item | Sound", meta = (ToolTip = "0 = Default\n1 = Wood\n2 = Glass\n3 = GlassBreak\n 4 = Rock\n5 = Heavy Metal\n6 = Bone\n7 = Anchor(small thing)\n8 = Book\n9 = Picture-frame(small woodish)\n10 = Torch(woord & metal)\n11 = Chair\n12 = Candle(metal)"))
	int MaterialInt = 0;

	// To setup KEY incase it's the key item to do comparation
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item | ID")
	FString ID;

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	virtual void OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	virtual void OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

};
