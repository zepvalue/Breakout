// Fill out your copyright notice in the Description page of Project Settings.

#include "Breakout/Widget/BreakoutHUD.h"
#include "Breakout/GameMode/BreakoutGameModeBase.h"

ABreakoutHUD::ABreakoutHUD()
{
}

void ABreakoutHUD::DrawHUD()
{
	Super::DrawHUD();
	
}

void ABreakoutHUD::BeginPlay()
{
	Super::BeginPlay();

	GameMode = Cast<ABreakoutGameModeBase>(GetWorld()->GetAuthGameMode());

	if(GameWidgetClass)
	{
		GameWidget = CreateWidget<UBreakoutUserWidget>(GetWorld(),GameWidgetClass);
		if(GameWidget)
		{
			GameWidget->AddToViewport();
		}
	}
}

void ABreakoutHUD::UpdateBrickText(int32 BricksBroken,int32 BricksInLevel)
{
	if(GameWidget)
	{
		GameWidget->SetBricksText(BricksBroken, BricksInLevel);
	}
}

void ABreakoutHUD::UpdateLivesText(int32 Lives)
{
	if(GameWidget)
	{
		GameWidget->SetLivesText(Lives);
	}
}

