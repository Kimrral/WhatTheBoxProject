// Fill out your copyright notice in the Description page of Project Settings.


#include "WTBoxGameStateBase.h"
#include "GameFramework/PlayerState.h"


TArray<APlayerState*> AWTBoxGameStateBase::GetPlayerListByScore()
{
	TArray<APlayerState*> playerList(PlayerArray);

	playerList.Sort([](const APlayerState& a, const APlayerState& b) {return a.GetScore() > b.GetScore(); });

	return playerList;
}
