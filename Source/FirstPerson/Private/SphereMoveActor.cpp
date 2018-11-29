// Fill out your copyright notice in the Description page of Project Settings.

#include "SphereMoveActor.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Particles/ParticleSystemComponent.h"

// Sets default values
ASphereMoveActor::ASphereMoveActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CollisionComp = CreateDefaultSubobject<USphereComponent>(TEXT("CollisionComp"));
	CollisionComp->InitSphereRadius(52.0f);
	CollisionComp->BodyInstance.SetCollisionProfileName(TEXT("PhysicsActor"));
	CollisionComp->OnComponentHit.AddDynamic(this, &ASphereMoveActor::OnHit);
	CollisionComp->OnComponentBeginOverlap.AddDynamic(this, &ASphereMoveActor::OnOverlayBegin);
	CollisionComp->OnComponentEndOverlap.AddDynamic(this, &ASphereMoveActor::OnOverlayEnd);
	// Players can't walk on it
	CollisionComp->SetWalkableSlopeOverride(FWalkableSlopeOverride(WalkableSlope_Unwalkable, 0.0f));
	CollisionComp->CanCharacterStepUpOn = ECB_No;
	RootComponent = CollisionComp;
	
	SphereMeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("SphereMeshComp"));
	SphereMeshComp->SetupAttachment(CollisionComp);
	static ConstructorHelpers::FObjectFinder<UStaticMesh> SphereMeshAsset(TEXT("/Game/StarterContent/Shapes/Shape_Sphere.Shape_Sphere"));
	if (SphereMeshAsset.Succeeded())
	{
		SphereMeshComp->SetStaticMesh(SphereMeshAsset.Object);
		SphereMeshComp->SetRelativeLocation(FVector(0.0f, 0.0f, 0.0f));
		SphereMeshComp->SetWorldScale3D(FVector(1.0f));
	}

	// 创建粒子系统以供我们激活或反激活
	ParticleComp = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("ParticleComp"));
	ParticleComp->SetupAttachment(CollisionComp);
	ParticleComp->bAutoActivate = false;
	ParticleComp->SetRelativeLocation(FVector(-20.0f, 0.0f, 20.0f));
	static ConstructorHelpers::FObjectFinder<UParticleSystem> ParticleAsset(TEXT("/Game/StarterContent/Particles/P_Fire.P_Fire"));
	if (ParticleAsset.Succeeded())
	{
		ParticleComp->SetTemplate(ParticleAsset.Object);
	}
}

// Called when the game starts or when spawned
void ASphereMoveActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASphereMoveActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ASphereMoveActor::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	UE_LOG(LogTemp, Warning, TEXT("ASphereMoveActor::OnHit"));
// 	if (GEngine)
// 	{
// 		GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Yellow, TEXT("@cpf ASphereMoveActor::OnHit"));
// 	}
	//ParticleComp->ActivateSystem(true);
}

void ASphereMoveActor::OnOverlayBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, 
	int32 OtherBodyIndex, bool bFromSweep, const FHitResult &SweepResult)
{
	UE_LOG(LogTemp, Warning, TEXT("ASphereMoveActor::OnOverlayBegin"));
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Yellow, TEXT("@cpf ASphereMoveActor::OnOverlayBegin"));
	}
}

void ASphereMoveActor::OnOverlayEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	UE_LOG(LogTemp, Warning, TEXT("ASphereMoveActor::OnOverlayEnd"));
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Yellow, TEXT("@cpf ASphereMoveActor::OnOverlayEnd"));
	}
}

