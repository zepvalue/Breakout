// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Breakout/Widget/BreakoutUserWidget.h"
#include "GameFramework/GameModeBase.h"
#include "BreakoutGameModeBase.generated.h"

class ABreakoutHUD;
/**
 * 
 */
UCLASS()
class BREAKOUT_API ABreakoutGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

protected:
	int32 BricksBroken = 0;
	int32 BricksInLevel = 0;
	int32 Lives = 3;
	bool bLsGameOver = false;
	virtual void BeginPlay() override;
	
public:
	void BrickBroken();
	void GameOver();
	void LoseLife(AActor*);
	void Respawn(AActor* );
	void GenerateBricks();


private:
	ABreakoutHUD* InGameHud;

};
