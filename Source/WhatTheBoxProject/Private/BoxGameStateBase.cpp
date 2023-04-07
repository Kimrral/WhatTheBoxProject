// Fill out your copyright notice in the Description page of Project Settings.


#include "BoxGameStateBase.h"
#include "GameFrameWork/PlayerState.h"


// �÷��̾� ������Ʈ ����Ʈ�� ���������� ������������ ������ �Լ�.
TArray<APlayerState*> ABoxGameStateBase::GetPlayerListByScore()
{
	TArray<APlayerState*> PlayerList = PlayerArray;

	// �������� ����
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
