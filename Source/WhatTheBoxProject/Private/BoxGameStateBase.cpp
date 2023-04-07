// Fill out your copyright notice in the Description page of Project Settings.


#include "BoxGameStateBase.h"
#include "GameFrameWork/PlayerState.h"


// 플레이어 스테이트 리스트를 점수에따라 내림차순으로 정렬할 함수.
TArray<APlayerState*> ABoxGameStateBase::GetPlayerListByScore()
{
	TArray<APlayerState*> PlayerList = PlayerArray;

	// 내림차순 정렬
	PlayerArray.Sort([](const APlayerState& A, const APlayerState& B) {
		return A.GetScore() > B.GetScore();
	});
	return PlayerList;
}
/*
TArray<APlayerState*> ABoxGameStateBase::GetGoPlayerListByScore()
{

}
*/
