// Fill out your copyright notice in the Description page of Project Settings.


#include "Ball.h"

// Sets default values
ABall::ABall()
{
	GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::White, TEXT("CONSTRUCTOR"));

 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	Mesh->SetSimulatePhysics(true);
	RootComponent = Mesh;


}

// Called when the game starts or when spawned
void ABall::BeginPlay()
{
	Super::BeginPlay();
	GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::White, TEXT("BEGIN PLAY"));

	
	constexpr float InitialX = 400;
	constexpr float InitialY = 400;
	
	const FVector Force = FVector(InitialX,InitialY,0);
	Mesh->AddForce(Force * MovementSpeed);
}

void ABall::Spawn()
{
		GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::White, TEXT("SPAWNING BALL"));

		const FVector Location(0.0f, 0.0f, 0.0f);
		const FRotator Rotation(0.0f, 0.0f, 0.0f);
		const FActorSpawnParameters SpawnInfo;
		GetWorld()->SpawnActor<ABall>(BallClassToSpawn, Location, Rotation, SpawnInfo);

}


