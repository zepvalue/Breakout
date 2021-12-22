// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
#include "BreakoutUserWidget.generated.h"


/**
 * 
 */
UCLASS()
class BREAKOUT_API UBreakoutUserWidget : public UUserWidget
{
	GENERATED_BODY()

public:

	UBreakoutUserWidget(const FObjectInitializer& ObjectInitializer);
	virtual void NativeConstruct() override;
	
	void SetBricksText(int32 BricksBroken, int32 BricksInLevel);
	void SetLivesText(int32 Lives);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UTextBlock* BricksText;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UTextBlock* LivesText;
	
};
