// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#include "FirstPersonGameMode.h"
#include "FirstPersonHUD.h"
#include "FirstPersonCharacter.h"
#include "UObject/ConstructorHelpers.h"
#include "Kismet/GameplayStatics.h"

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
		UE_LOG(LogTemp, Warning, TEXT("Disable pawn Input!"));
		//��ֹ�������
		InstigatorPawn->DisableInput(nullptr);
		
		//�����ӵ��ƶ�
		if (SpectatingViewPointClass)
		{
			TArray<AActor*> ReturnedActors;
			//����ָ�����͵�Actor
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
	OnMissionCompleted(InstigatorPawn);
}
