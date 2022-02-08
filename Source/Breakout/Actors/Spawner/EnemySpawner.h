// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ObjectPool.h"
#include "Components/BoxComponent.h"
#include "GameFramework/Actor.h"
#include "EnemySpawner.generated.h"

UCLASS()
class LAYSOFALTHAS_API AEnemySpawner : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AEnemySpawner();
	FVector GetRandomPointInVolume();


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	void Spawn();

private:
	UBoxComponent* SpawnVolume;
	
	UPROPERTY(EditAnywhere, Category = "Spawner")	
	UObjectPool* ObjectPool;

	FTimerHandle SpawnCooldownTimer;
	
	UPROPERTY(EditAnywhere, Category = "Spawner")
	float SpawnCooldown = 1.2f;
};
