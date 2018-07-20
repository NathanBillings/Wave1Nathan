// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#include "SurviveConceptGameMode.h"
#include "SurviveConceptHUD.h"
#include "SurviveConceptCharacter.h"
#include "UObject/ConstructorHelpers.h"

ASurviveConceptGameMode::ASurviveConceptGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPersonCPP/Blueprints/FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

	// use our custom HUD class
	HUDClass = ASurviveConceptHUD::StaticClass();
}
