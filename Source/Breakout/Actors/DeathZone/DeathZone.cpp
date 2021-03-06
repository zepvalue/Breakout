// Fill out your copyright notice in the Description page of Project Settings.


#include "DeathZone.h"
#include "Breakout/GMode/BreakoutGameModeBase.h"


ADeathZone::ADeathZone()
{
}

void ADeathZone::BeginPlay()
{
	Super::BeginPlay();
	OnActorBeginOverlap.AddDynamic(this, &ADeathZone::OnBeginOverlap);
}

//Let the gamemode handle the respawning on LoseLife
void ADeathZone::OnBeginOverlap(AActor* OverlappedActor,AActor* OtherActor)
{
	ABreakoutGameModeBase* GameMode = Cast<ABreakoutGameModeBase>(GetWorld()->GetAuthGameMode());
	if(GameMode) GameMode->LoseLife(OtherActor);
}


