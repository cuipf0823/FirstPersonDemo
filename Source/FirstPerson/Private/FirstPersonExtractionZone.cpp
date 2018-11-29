// Fill out your copyright notice in the Description page of Project Settings.

#include "FirstPersonExtractionZone.h"
#include "Components/BoxComponent.h"
#include "Components/DecalComponent.h"
#include "FirstPersonCharacter.h"
#include "FirstPersonGameMode.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AFirstPersonExtractionZone::AFirstPersonExtractionZone()
{
	OverlapComp = CreateDefaultSubobject<UBoxComponent>(TEXT("OverlapComp"));
	OverlapComp->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	OverlapComp->SetCollisionResponseToAllChannels(ECR_Ignore);
	OverlapComp->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
	OverlapComp->SetBoxExtent(FVector(200.0f));
	RootComponent = OverlapComp;
	OverlapComp->SetHiddenInGame(false);
	OverlapComp->OnComponentBeginOverlap.AddDynamic(this, &AFirstPersonExtractionZone::OnOverlayBegin);

	DecalComp = CreateDefaultSubobject<UDecalComponent>(TEXT("DecalComp"));
	DecalComp->DecalSize = FVector(200.0f, 200.0f, 200.0f);
	DecalComp->SetupAttachment(RootComponent);
}

void AFirstPersonExtractionZone::OnOverlayBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult &SweepResult)
{
	UE_LOG(LogTemp, Log, TEXT("Overlapped with extraction zone!"));
	AFirstPersonCharacter* FPSCharacter = Cast<AFirstPersonCharacter>(OtherActor);
	if (FPSCharacter == nullptr)
	{
		return;
	}

	if (FPSCharacter->bIsCarryingObjective)
	{
		AFirstPersonGameMode* GameMode = Cast<AFirstPersonGameMode>(GetWorld()->GetAuthGameMode());
		if (GameMode != nullptr)
		{
			GameMode->CompleteMission(FPSCharacter);
		}
	}
	else
	{
		UGameplayStatics::PlaySound2D(this, ObjectiveMissingSound);
		UE_LOG(LogTemp, Log, TEXT("Overlapped with extraction zone PlaySound2D!"));
	}
}

