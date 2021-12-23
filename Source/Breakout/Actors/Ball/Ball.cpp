// Fill out your copyright notice in the Description page of Project Settings.


#include "Ball.h"

// Sets default values
ABall::ABall()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	Mesh->SetSimulatePhysics(true);
	RootComponent = Mesh;
}

void ABall::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
}

// Called when the game starts or when spawned
void ABall::BeginPlay()
{
	Super::BeginPlay();

	constexpr float InitialX = 400;
	constexpr float InitialY = 400;
	
	const FVector Force = FVector(InitialX,InitialY,0);
	Mesh->AddForce(Force * MovementSpeed);
}






