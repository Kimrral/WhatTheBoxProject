// Fill out your copyright notice in the Description page of Project Settings.


#include "GameOverWidget.h"

#include "RankSlotWidget.h"
#include "Components/ScrollBox.h"
#include "Components/TextBlock.h"
#include "Components/ScrollBox.h"

//게임이 끝나면
//게임 오버 위젯이 뜨고
//플레이어 랭크 순서대로
//슬롯이 뜰것이다.
void UGameOverWidget::AddNewSlot(float ping, FString playerName, int32 score, int32 killSocre, int32 death)
{
	URankSlotWidget* rankSlot = CreateWidget<URankSlotWidget>(this, rankSlotWidget);
	if(rankSlot != nullptr)
	{
		rankSlot->text_pingNumber->SetText(FText::FromString(FString::Printf(TEXT("%f"), ping)));
		rankSlot->text_playerName->SetText(FText::FromString(playerName));
		rankSlot->text_finalScore->SetText(FText::FromString(FString::Printf(TEXT("%d"))));
		rankSlot->text_finalKillScore->SetText(FText::FromString(FString::Printf(TEXT("%d"))));
		rankSlot->text_finalDeaths->SetText(FText::FromString(FString::Printf(TEXT("%d"))));
		sbox_RankList->AddChild(rankSlot);
	}
}
