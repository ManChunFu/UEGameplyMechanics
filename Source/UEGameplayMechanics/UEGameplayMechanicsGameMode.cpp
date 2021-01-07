// Copyright Epic Games, Inc. All Rights Reserved.

#include "UEGameplayMechanicsGameMode.h"
#include "UEGameplayMechanicsCharacter.h"
#include "UObject/ConstructorHelpers.h"

AUEGameplayMechanicsGameMode::AUEGameplayMechanicsGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/Blueprints/BP_Player"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
