// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#include "FirstPersonGameMode.h"
#include "FirstPersonHUD.h"
#include "FirstPersonCharacter.h"
#include "UObject/ConstructorHelpers.h"

AFirstPersonGameMode::AFirstPersonGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPersonCPP/Blueprints/FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

	// use our custom HUD class
	HUDClass = AFirstPersonHUD::StaticClass();
}

void AFirstPersonGameMode::CompleteMission(APawn* InstigatorPawn)
{
	if (InstigatorPawn != nullptr)
	{
		//½ûÖ¹Íæ¼ÒÊäÈë
		InstigatorPawn->DisableInput(nullptr);
		UE_LOG(LogTemp, Warning, TEXT("Disable pawn Input!"));
	}
	OnMissionCompleted(InstigatorPawn);
}
