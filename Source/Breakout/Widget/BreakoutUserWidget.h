// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "BreakoutUserWidget.generated.h"

/**
 * 
 */
UCLASS()
class BREAKOUT_API UBreakoutUserWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintImplementableEvent)
	void SetItemText(int32 BricksBroken, int32 BricksInLevel);
	
};
