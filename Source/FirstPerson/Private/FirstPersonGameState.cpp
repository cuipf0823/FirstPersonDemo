// Fill out your copyright notice in the Description page of Project Settings.

#include "FirstPersonGameState.h"
#include "FirstPersonPlayerController.h"


void AFirstPersonGameState::MulticastOnMissionComplete_Implementation(APawn* InstigatorPawn, bool bGameOver)
{
// 	for (FConstPawnIterator it = GetWorld()->GetPawnIterator(); it; ++it)
// 	{
// 		APawn* Pawn = it->Get();
// 		if (Pawn && Pawn->IsLocallyControlled())
// 		{
// 			//������ҽ�ֹ��Ϸ����
// 			Pawn->DisableInput(nullptr);
// 		}
// 	}

	for (auto it = GetWorld()->GetPlayerControllerIterator(); it; ++it)
	{
		AFirstPersonPlayerController* PC = Cast<AFirstPersonPlayerController>(it->Get());
		if (PC && PC->IsLocalController())
		{
			PC->OnMissionCompleted(InstigatorPawn, bGameOver);
		}
		
		//��ֹ��ұ�������
		APawn* MyPawn = PC->GetPawn();
		if (MyPawn)
		{
			MyPawn->DisableInput(PC);
		}
	}
}
