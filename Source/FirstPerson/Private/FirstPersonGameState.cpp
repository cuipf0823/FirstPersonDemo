// Fill out your copyright notice in the Description page of Project Settings.

#include "FirstPersonGameState.h"


void AFirstPersonGameState::MulticastOnMissionComplete_Implementation(APawn* InstigatorPawn, bool bGameOver)
{
	for (FConstPawnIterator it = GetWorld()->GetPawnIterator(); it; ++it)
	{
		APawn* Pawn = it->Get();
		if (Pawn && Pawn->IsLocallyControlled())
		{
			//������ҽ�ֹ��Ϸ����
			Pawn->DisableInput(nullptr);
		}
	}
}
