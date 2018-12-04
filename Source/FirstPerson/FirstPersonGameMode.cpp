// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#include "FirstPersonGameMode.h"
#include "FirstPersonHUD.h"
#include "FirstPersonCharacter.h"
#include "UObject/ConstructorHelpers.h"
#include "Kismet/GameplayStatics.h"
#include "FirstPersonGameState.h"

AFirstPersonGameMode::AFirstPersonGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPersonCPP/Blueprints/BP_FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

	// use our custom HUD class
	HUDClass = AFirstPersonHUD::StaticClass();
	GameStateClass = AFirstPersonGameState::StaticClass();
}

void AFirstPersonGameMode::CompleteMission(APawn* InstigatorPawn, bool bGameOver /*= false*/)
{
	if (InstigatorPawn != nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("Disable pawn Input!"));
		
		//设置视点移动
		if (SpectatingViewPointClass)
		{
			TArray<AActor*> ReturnedActors;
			//查找指定类型的Actor
			UGameplayStatics::GetAllActorsOfClass(this, SpectatingViewPointClass, ReturnedActors);
			if (ReturnedActors.Num() > 0)
			{
				AActor* NewViewTarget = ReturnedActors[0];
				APlayerController* PC = Cast<APlayerController>(InstigatorPawn->GetController());
				if (PC != nullptr)
				{
					PC->SetViewTargetWithBlend(NewViewTarget, 0.5f, VTBlend_Cubic);
				}
			}
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("SpectatingViewPointClass is invaild"));
		}

	}

	AFirstPersonGameState* GS = GetGameState<AFirstPersonGameState>();
	if (GS != nullptr)
	{

		GS->MulticastOnMissionComplete(InstigatorPawn, bGameOver);
	}
	OnMissionCompleted(InstigatorPawn, bGameOver);
}
