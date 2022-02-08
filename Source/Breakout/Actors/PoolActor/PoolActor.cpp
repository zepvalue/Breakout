// Fill out your copyright notice in the Description page of Project Settings.
#include "PoolActor.h"

// Sets default values
APoolActor::APoolActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

void APoolActor::SetActive(bool BlnFlag)
{
	BlnActive =  BlnFlag;
	SetActorHiddenInGame(!BlnFlag);
}

bool APoolActor::isActive()
{
	return BlnActive;
}

// Called when the game starts or when spawned
void APoolActor::BeginPlay()
{
	Super::BeginPlay();
	
}

void APoolActor::Deactivate()
{
	SetActive(false);
}


