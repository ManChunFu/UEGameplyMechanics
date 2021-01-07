// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "UEGameplayMechanicsCharacter.generated.h"

UCLASS(config = Game)
class AUEGameplayMechanicsCharacter : public ACharacter
{
	GENERATED_BODY()

		/** Camera boom positioning the camera behind the character */
		UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
		class USpringArmComponent* CameraBoom;

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
		class UCameraComponent* FollowCamera;
public:
	AUEGameplayMechanicsCharacter();

	/** Base turn rate, in deg/sec. Other scaling may affect final turn rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
		float BaseTurnRate;

	/** Base look up/down rate, in deg/sec. Other scaling may affect final rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
		float BaseLookUpRate;

	/* My codes*/
	/*============================================================================*/
	/** Setup Noise Emitter so AI can hear*/
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Noise")
	class UPawnNoiseEmitterComponent* NoiseEmitter;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category ="Noise")
	bool bEnableSprintNoise;

	/* Over this value is sprinting, this will determine if the Actor should make noise */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Noise", meta = (EditCondition = "bEnableSprintNoise == true"))
	float MaxWalkingSpeed;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Noise", meta = (EditCondition = "bEnableSprintNoise == true"))
	float SprintLoudness;

	/* Should the Actor make noise when landing on the ground after jumping */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Noise", meta = (EditCondition = "bEnableSprintNoise == true"))
	bool bEnableLandingNoise;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Noise", meta = (EditCondition = "bEnableLandingNoise == true"))
	float LandingLoudness;
	/* ===================================================================================================================*/
protected:

	/** Resets HMD orientation in VR. */
	void OnResetVR();

	/** Called for forwards/backward input */
	void MoveForward(float Value);

	/** Called for side to side input */
	void MoveRight(float Value);

	/**
	 * Called via input to turn at a given rate.
	 * @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	 */
	void TurnAtRate(float Rate);

	/**
	 * Called via input to turn look up/down at a given rate.
	 * @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	 */
	void LookUpAtRate(float Rate);

	/** Handler for when a touch input begins. */
	void TouchStarted(ETouchIndex::Type FingerIndex, FVector Location);

	/** Handler for when a touch input stops. */
	void TouchStopped(ETouchIndex::Type FingerIndex, FVector Location);

protected:
	// APawn interface
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	// End of APawn interface

public:
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	/** Returns FollowCamera subobject **/
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }

	/* My codes*/
	/*============================================================================*/
	/* Make sound if it meets requirements*/
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	virtual void Jump() override;

private:
	float MinFallingSpeed;
	FVector Velocity;
	bool IsSprinting();
	void CheckShouldMakeSound();
	void MakeSound(float Value);
	/*============================================================================*/
};

