// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameState.h"
#include "BoxGameStateBase.generated.h"

/**
 * 
 */
UCLASS()
class WHATTHEBOXPROJECT_API ABoxGameStateBase : public AGameState
{
	GENERATED_BODY()

public:
	// 점수배열
	TArray<class APlayerState*> GetPlayerListByScore();

	//TArray<class APlayerState*> GetGoPlayerListByScore();
};
