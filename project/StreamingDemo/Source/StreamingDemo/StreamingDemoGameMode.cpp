// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#include "StreamingDemoGameMode.h"
#include "StreamingDemoHUD.h"
#include "StreamingDemoCharacter.h"
#include "UObject/ConstructorHelpers.h"

AStreamingDemoGameMode::AStreamingDemoGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPersonCPP/Blueprints/FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

	// use our custom HUD class
	HUDClass = AStreamingDemoHUD::StaticClass();
}
