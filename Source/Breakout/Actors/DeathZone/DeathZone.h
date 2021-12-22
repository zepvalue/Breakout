// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/TriggerBox.h"
#include "DeathZone.generated.h"

class ABall;
/**
 * 
 */
UCLASS()
class BREAKOUT_API ADeathZone : public ATriggerBox
{
	GENERATED_BODY()

public:
	ADeathZone();

protected:
	virtual void BeginPlay() override;

	UFUNCTION()
	void OnBeginOverlap(AActor* OverlappedActor, AActor* OtherActor);
	
};
