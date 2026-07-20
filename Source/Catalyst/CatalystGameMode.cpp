// Copyright Epic Games, Inc. All Rights Reserved.

#include "CatalystGameMode.h"
#include "CatalystCharacter.h"
#include "UObject/ConstructorHelpers.h"

ACatalystGameMode::ACatalystGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
