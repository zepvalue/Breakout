// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PoolActor.generated.h"

UCLASS()
class LAYSOFALTHAS_API APoolActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APoolActor();
	void SetActive(bool BlnActive);
	bool isActive();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	void Deactivate();
private:
	bool BlnActive;

};
