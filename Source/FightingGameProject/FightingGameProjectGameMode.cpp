// Copyright Epic Games, Inc. All Rights Reserved.

#include "FightingGameProjectGameMode.h"
#include "UObject/ConstructorHelpers.h"

AFightingGameProjectGameMode::AFightingGameProjectGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/Characters/GasmaskGuy/BP_GasmaskGuy"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
