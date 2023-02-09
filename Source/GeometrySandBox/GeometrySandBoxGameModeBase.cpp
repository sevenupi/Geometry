// Copyright Epic Games, Inc. All Rights Reserved.


#include "GeometrySandBoxGameModeBase.h"
#include  "SandBoxPawn.h"
#include  "SanboxPlayerController.h"

AGeometrySandBoxGameModeBase::AGeometrySandBoxGameModeBase()
{
	DefaultPawnClass = ASandBoxPawn::StaticClass();
	PlayerControllerClass = ASanboxPlayerController::StaticClass();
}


