// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "BoxGameStateBase.generated.h"

/**
 * 
 */
UCLASS()
class WHATTHEBOXPROJECT_API ABoxGameStateBase : public AGameStateBase
{
	GENERATED_BODY()

public:
	// 점수배열
	TArray<class APlayerState*> GetPlayerListByScore();
	
};
