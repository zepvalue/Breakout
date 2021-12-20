// Fill out your copyright notice in the Description page of Project Settings.


#include "Paddle.h"

#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"

// Sets default values
APaddle::APaddle()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");

	RootComponent = Mesh;
	Mesh->SetSimulatePhysics(true);
}

// Called every frame
void APaddle::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if(!MovementDirection.IsZero())
	{
		const FVector NewLocation = GetActorLocation() + (MovementDirection * DeltaTime * MovementSpeed) ;
		SetActorLocation(NewLocation);
	}

}



// Called when the game starts or when spawned
void APaddle::BeginPlay()
{
	Super::BeginPlay();

	//Calculate the MoveForce based on mass
	MoveForce *= Mesh->GetMass();
}

void APaddle::MoveHorizontal(float const Value)
{
	MovementDirection.X = FMath::Clamp(Value,-1.0f,1.0f);
}

// Called to bind functionality to input
void APaddle::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	InputComponent->BindAxis("MoveHorizontal",this,&APaddle::MoveHorizontal);
}

