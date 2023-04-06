// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "WTBoxGameStateBase.generated.h"

/**
 * 
 */
UCLASS()
class WHATTHEBOXPROJECT_API AWTBoxGameStateBase : public AGameStateBase
{
	GENERATED_BODY()
public:
	//플레이어 점수대로 화면 우측 상단에 띄울것
	TArray<class APlayerState*> GetPlayerListByScore();

	//플레이가 끝난후 최종 점수를 순서대로 띄울것


};
