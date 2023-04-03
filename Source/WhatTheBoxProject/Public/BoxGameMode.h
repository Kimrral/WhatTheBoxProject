// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "BoxGameMode.generated.h"

/**
 * 
 */
UCLASS()
class WHATTHEBOXPROJECT_API ABoxGameMode : public AGameMode
{
	GENERATED_BODY()
	
public:
UPROPERTY(EditAnywhere, Replicated)
TArray<FString> KillLog;

// 킬로그 더하는 함수
void AddKillLog(const FString& KillerName, const FString& VictimName);
};
