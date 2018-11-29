// Fill out your copyright notice in the Description page of Project Settings.

#include "FirstPersonAIGuard.h"
#include "Perception/PawnSensingComponent.h"
#include "DrawDebugHelpers.h"

// Sets default values
AFirstPersonAIGuard::AFirstPersonAIGuard()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	PawnSensingComp = CreateDefaultSubobject<UPawnSensingComponent>(TEXT("PawnSensingComp"));
	UE_LOG(LogTemp, Warning, TEXT("AFirstPersonAIGuard::AFirstPersonAIGuard"));
}

// Called when the game starts or when spawned
void AFirstPersonAIGuard::BeginPlay()
{
	Super::BeginPlay();
	//ע�ᶯ̬��Ӧ���ڹ��캯����, �޷���Ӧ; ����BeginPlay��, ����������Ӧ;��ʱԭ��֪��?
	PawnSensingComp->OnSeePawn.AddDynamic(this, &AFirstPersonAIGuard::OnPawnSeen);
	PawnSensingComp->OnHearNoise.AddDynamic(this, &AFirstPersonAIGuard::OnHearNoise);
}

void AFirstPersonAIGuard::OnPawnSeen(APawn* SeenPawn)
{
	UE_LOG(LogTemp, Warning, TEXT("AFirstPersonAIGuard::OnPawnSeen"));
	if (SeenPawn == nullptr)
	{
		return;
	}
	DrawDebugSphere(GetWorld(), SeenPawn->GetActorLocation(), 32.0f, 12, FColor::Yellow, false, 4.0f);
}

void AFirstPersonAIGuard::OnHearNoise(APawn* Instigator, const FVector& Location, float Volume)
{

}

// Called every frame
void AFirstPersonAIGuard::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


