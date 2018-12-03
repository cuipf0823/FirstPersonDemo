// Fill out your copyright notice in the Description page of Project Settings.

#include "FirstPersonObjectiveActor.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/Actor.h"
#include "FirstPersonCharacter.h"

// Sets default values
AFirstPersonObjectiveActor::AFirstPersonObjectiveActor()
{
	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComp"));
	MeshComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	RootComponent = MeshComp;

	SphereComp = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComp"));
	SphereComp->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	SphereComp->SetCollisionResponseToAllChannels(ECR_Ignore);
	//人性通道设置为响应通道, 设为发生重叠
	SphereComp->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
	SphereComp->SetupAttachment(MeshComp);

	//设置actor复制
	SetReplicates(true);
}

// Called when the game starts or when spawned
void AFirstPersonObjectiveActor::BeginPlay()
{
	Super::BeginPlay();
	PlayEffects();
	
}

void AFirstPersonObjectiveActor::PlayEffects()
{
	UGameplayStatics::SpawnEmitterAtLocation(this, PickupFX, GetActorLocation());
}

void AFirstPersonObjectiveActor::NotifyActorBeginOverlap(AActor* OtherActor)
{

	UE_LOG(LogTemp, Log, TEXT("AFirstPersonObjectiveActor::NotifyActorBeginOverlap"))
	Super::NotifyActorBeginOverlap(OtherActor);
	PlayEffects();

	if (Role == ROLE_Authority)
	{
		AFirstPersonCharacter* FPSCharacter = Cast<AFirstPersonCharacter>(OtherActor);
		if (FPSCharacter != nullptr)
		{
			FPSCharacter->bIsCarryingObjective = true;
			Destroy();
		}
	}
}
