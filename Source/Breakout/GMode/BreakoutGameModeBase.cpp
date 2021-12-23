// Copyright Epic Games, Inc. All Rights Reserved.


#include "BreakoutGameModeBase.h"
#include "Breakout/actors/Ball/Ball.h"
#include "Breakout/Actors/Brick/Brick.h"
#include "Breakout/Widget/BreakoutHUD.h"
#include "Kismet/GameplayStatics.h"

/**
 * BeginPlay initializes the scene.
 *
 * Initialiaze the fields and the gameHUD
 *
 * @param None
 * @return void
 */
//TODO: Add brick generation on BeginPlay with different color applied
void ABreakoutGameModeBase::BeginPlay()
{
	Super::BeginPlay();
	TArray<AActor*> Bricks;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(),ABrick::StaticClass(), Bricks);
	BricksInLevel = Bricks.Num();
	InGameHud = Cast<ABreakoutHUD>(GetWorld()->GetFirstPlayerController()->GetHUD());
}

/**
 * keeps track of the broken bricks.
 *
 * Keeps track of the broken bricks and updates the HUD
 *
 * @param None
 * @return void
 */

void ABreakoutGameModeBase::BrickBroken()
{
	BricksBroken++;
	if(InGameHud)
	{
		InGameHud->UpdateBrickText(BricksBroken,BricksInLevel);
	}
}

void ABreakoutGameModeBase::GameOver()
{
	bLsGameOver = true;
	InGameHud->DrawGameOverText();
	//Destroy all actors
}

/**
 * Decrement the lives variable in the GameMode.
 *
 * Decrements the lives counter in the GameMode to keep track of remaining lives 
 *
 * @param OtherActor value of the actor overlapping the DeathZone.
 * @return void
 */
void ABreakoutGameModeBase::LoseLife(AActor* OtherActor)
{
	if(Lives > 0)
	{
		Lives--;
		InGameHud->UpdateLivesText(Lives);
		Respawn(OtherActor);
	} else
		GameOver();
}

/**
 * Reset the position of the Ball.
 *
 * Reset the position of the ball if player still have lives
 *
 * @param OtherActor value of the actor overlapping the DeathZone.
 * @return void
 */
void ABreakoutGameModeBase::Respawn(AActor* OtherActor)
{
	ABall* Ball = Cast<ABall>(OtherActor);
	Ball->SetActorLocation(FVector(-10.f,-10.f,0.f));
}
