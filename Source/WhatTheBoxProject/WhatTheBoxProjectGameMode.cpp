// Copyright Epic Games, Inc. All Rights Reserved.

#include "WhatTheBoxProjectGameMode.h"
#include "WhatTheBoxProjectCharacter.h"
#include "UObject/ConstructorHelpers.h"

AWhatTheBoxProjectGameMode::AWhatTheBoxProjectGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
