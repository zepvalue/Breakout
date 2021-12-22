// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "BreakoutHUD.generated.h"

class UBreakoutUserWidget;
class ABreakoutGameModeBase;
/**
 * 
 */
UCLASS()
class BREAKOUT_API ABreakoutHUD : public AHUD
{
	GENERATED_BODY()

public:

	ABreakoutHUD();
	
	virtual void DrawHUD() override;
	virtual void BeginPlay() override;

	UFUNCTION()
	void UpdateBrickText(int32 BricksBroken, int32 BricksInLevel);
	UFUNCTION()
	void UpdateLivesText(int32 Lives);
	UFUNCTION()
	void DrawGameOverText();

protected:
	UPROPERTY(EditDefaultsOnly, Category = "Interactive")
	TSubclassOf<class UUserWidget> GameWidgetClass;

private:
	UPROPERTY()
	UBreakoutUserWidget* GameWidget;

	
	ABreakoutGameModeBase* GameMode;
	
};
