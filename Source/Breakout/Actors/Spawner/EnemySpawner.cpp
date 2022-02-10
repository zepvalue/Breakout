// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemySpawner.h"
#include "PoolActor.h"
#include "Kismet/KismetMathLibrary.h"

// Sets default values
AEnemySpawner::AEnemySpawner()
{
	SpawnVolume = CreateDefaultSubobject<UBoxComponent>(TEXT("SpawnVolume"));
	RootComponent = SpawnVolume;
	
	ObjectPool = CreateDefaultSubobject<UObjectPool>(TEXT("ObjectPooler"));
	
}

// Called when the game starts or when spawned
void AEnemySpawner::BeginPlay()
{
	Super::BeginPlay();
	GetWorldTimerManager().SetTimer(SpawnCooldownTimer, this, &AEnemySpawner::Spawn, SpawnCooldown, false);
}

FVector AEnemySpawner::GetRandomPointInVolume() {
	FVector SpawnOrigin = SpawnVolume->Bounds.Origin;
	FVector SpawnExtent = SpawnVolume->Bounds.BoxExtent;
	return UKismetMathLibrary::RandomPointInBoundingBox(SpawnOrigin, SpawnExtent);
}

void AEnemySpawner::Spawn()
{
	APoolActor* PoolActor = ObjectPool->GetPoolActor();
	
	/* pool is drained */
	if (PoolActor == nullptr) {
		UE_LOG(LogTemp, Warning, TEXT("Cannot spawn - object pool drained. Retrying in %f seconds."), SpawnCooldown);
		GetWorldTimerManager().SetTimer(SpawnCooldownTimer, this, &AEnemySpawner::Spawn, SpawnCooldown, false);
		return;
	}
	const FVector ActorLocation = GetRandomPointInVolume();
	PoolActor->SetActorLocation(ActorLocation);
	PoolActor->SetActive(true);
	GetWorldTimerManager().SetTimer(SpawnCooldownTimer, this, &AEnemySpawner::Spawn, SpawnCooldown, false);
}

