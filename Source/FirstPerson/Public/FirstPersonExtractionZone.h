// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FirstPersonExtractionZone.generated.h"

class UBoxComponent;
class UDecalComponent;
UCLASS()
class FIRSTPERSON_API AFirstPersonExtractionZone : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AFirstPersonExtractionZone();

protected:
	UPROPERTY(VisibleAnywhere, Category = "Components")
	UBoxComponent* OverlapComp;

	// �������
	UPROPERTY(VisibleAnywhere, Category = "Components")
	UDecalComponent* DecalComp;

	UPROPERTY(EditDefaultsOnly, Category = "Sounds")
	USoundBase* ObjectiveMissingSound;

public:	
	UFUNCTION()
	void OnOverlayBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
			int32 OtherBodyIndex, bool bFromSweep, const FHitResult &SweepResult);
};
