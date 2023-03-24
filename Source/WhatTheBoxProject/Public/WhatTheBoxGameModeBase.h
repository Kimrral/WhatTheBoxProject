// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "WhatTheBoxGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class WHATTHEBOXPROJECT_API AWhatTheBoxGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
	
public:
	AWhatTheBoxGameModeBase();


public:
	virtual void BeginPlay() override;


	// �ð�
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Time")
		int32 GameTime;

	// ���� ���۽�, 5�� ī��Ʈ �ٿ�
	void GameStartCountDown();
	
	FTimerHandle PlayTimeCount;
};
