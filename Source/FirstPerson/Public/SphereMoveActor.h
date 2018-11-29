// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SphereMoveActor.generated.h"

UCLASS()
class FIRSTPERSON_API ASphereMoveActor : public AActor
{
	GENERATED_BODY()
	
public:
	// Sets default values for this actor's properties
	ASphereMoveActor();

	UPROPERTY(VisibleAnywhere, Category = "SphereMove")
	class USphereComponent* CollisionComp;

	UPROPERTY(VisibleAnywhere, Category = "SphereMove")
	class UStaticMeshComponent* SphereMeshComp;
	
	UPROPERTY(VisibleAnywhere, Category = "ShpereMove")
	class UParticleSystemComponent* ParticleComp;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);
	UFUNCTION()
	virtual void OnOverlayBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, 
		int32 OtherBodyIndex, bool bFromSweep, const FHitResult &SweepResult);
	UFUNCTION()
	virtual void OnOverlayEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

};
