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
	OriginRotator = GetActorRotation();
}

// Called when the game starts or when spawned
void AFirstPersonAIGuard::BeginPlay()
{
	Super::BeginPlay();
	//注册动态响应放在构造函数中, 无法响应; 放在BeginPlay中, 正常可以响应;暂时原因不知道?
	PawnSensingComp->OnSeePawn.AddDynamic(this, &AFirstPersonAIGuard::OnPawnSeen);
	PawnSensingComp->OnHearNoise.AddDynamic(this, &AFirstPersonAIGuard::OnHearNoise);
}

void AFirstPersonAIGuard::ResetOrientation()
{
	SetActorRotation(OriginRotator);
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

void AFirstPersonAIGuard::OnHearNoise(APawn* NoiseInstigator, const FVector& Location, float Volume)
{
	DrawDebugSphere(GetWorld(), Location, 32.0f, 12, FColor::Green, false, 10.0f);

	//AI guard听到声音之后朝向声音方向转动
	//FRotationMatrix::MakeFromX()
	FVector Direction = Location - GetActorLocation();
	//转化为单位向量
	Direction.Normalize();
	FRotator NewLookAt = FRotationMatrix::MakeFromX(Direction).Rotator();
	NewLookAt.Pitch = 0.0f;
	NewLookAt.Roll = 0.0f;
	SetActorRotation(NewLookAt);

	//设置方向回正定时器
	if (GetWorldTimerManager().IsTimerActive(TimeResetOrientation))
	{
		GetWorldTimerManager().ClearTimer(TimeResetOrientation);
	}
	GetWorldTimerManager().SetTimer(TimeResetOrientation, this, &AFirstPersonAIGuard::ResetOrientation, 3.0f);
}

// Called every frame
void AFirstPersonAIGuard::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


