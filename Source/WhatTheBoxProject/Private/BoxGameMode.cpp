// Fill out your copyright notice in the Description page of Project Settings.


#include "BoxGameMode.h"
#include "WhatTheBoxGameModeBase.h"
#include "Net/UnrealNetwork.h"

void ABoxGameMode::AddKillLog(const FString& KillerName, const FString& VictimName)
{
	// 킬로그에 추가
	FString KillLogString = FString::Printf(TEXT("%s killed %s"), *KillerName, *VictimName);
	KillLog.Add(KillLogString);
// 	FString KillMessage = KillerName + TEXT(" killed ") + VictimName;
// 	KillLog.Add(KillMessage);
}

void ABoxGameMode::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ABoxGameMode, KillLog);
}
