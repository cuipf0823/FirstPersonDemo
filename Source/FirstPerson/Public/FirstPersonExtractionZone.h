// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FirstPersonExtractionZone.generated.h"

class UBoxComponent;
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

public:	
	UFUNCTION()
	void OnOverlayBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
			int32 OtherBodyIndex, bool bFromSweep, const FHitResult &SweepResult);
};
