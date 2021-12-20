// Fill out your copyright notice in the Description page of Project Settings.


#include "Brick.h"

#include "BreakoutGameModeBase.h"

// Sets default values
ABrick::ABrick()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	RootComponent = Mesh;


}

// Called when the game starts or when spawned
void ABrick::BeginPlay()
{
	Super::BeginPlay();

	Mesh->OnComponentHit.AddDynamic(this, &ABrick::onHit);

	
}

void ABrick::onHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	FVector NormalImpulse, const FHitResult& Hit)
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::White, TEXT("HIT"));
}

void ABrick::Collected_Implementation()
{
	ABreakoutGameModeBase* GameMode = Cast<ABreakoutGameModeBase>(GetWorld()->GetAuthGameMode());
	if(GameMode) GameMode->BrickBroken();
}

