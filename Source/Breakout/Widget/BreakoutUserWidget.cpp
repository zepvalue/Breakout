// Fill out your copyright notice in the Description page of Project Settings.


#include "BreakoutUserWidget.h"

UBreakoutUserWidget::UBreakoutUserWidget(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
}

void UBreakoutUserWidget::NativeConstruct()
{
	Super::NativeConstruct();
	GameOverText->SetVisibility(ESlateVisibility::Hidden);
}

void UBreakoutUserWidget::SetBricksText(int32 BricksBroken, int32 BricksInLevel)
{
	BricksText->SetText(FText::FromString(FString::Printf(TEXT("Bricks %d / %d"), BricksBroken,BricksInLevel)));
}

void UBreakoutUserWidget::SetLivesText(int32 Lives)
{
	LivesText->SetText(FText::FromString(FString::Printf(TEXT("Lives %d"), Lives)));
}

void UBreakoutUserWidget::SetGameOverText()
{
	GameOverText->SetVisibility(ESlateVisibility::Visible);
	GameOverText->SetText(FText::FromString(FString::Printf(TEXT("GAME OVER"))));
}




