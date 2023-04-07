// Fill out your copyright notice in the Description page of Project Settings.


#include "GameOverWidget.h"

#include "RankSlotWidget.h"
#include "Components/ScrollBox.h"
#include "Components/TextBlock.h"
#include "Components/ScrollBox.h"
#include  "BoxGameStateBase.h"
#include  "WTBoxGameInstance.h"
#include "BoxMainWidget.h"

//게임이 끝나면
//게임 오버 위젯이 뜨고
//플레이어 랭크 순서대로
//슬롯이 뜰것이다.
void UGameOverWidget::AddNewSlot()
{
	URankSlotWidget* rankSlot = CreateWidget<URankSlotWidget>(this, rankSlotWidget);
	UWTBoxGameInstance* gameInstance = Cast<UWTBoxGameInstance>(GetGameInstance());
	AGameStateBase* gameState = Cast<AGameStateBase>(GetWorld()->GetGameState());
	//UBoxMainWidget* boxMainWidget = Cast<UBoxMainWidget>
	
	if(rankSlot != nullptr)
	{
		rankSlot->text_pingNumber->SetText(FText::FromString(FString::Printf(TEXT("%f"), gameInstance->sessionSearchInfo.ping)));
		rankSlot->text_playerName->SetText(FText::FromName(gameInstance->sessionID));
		rankSlot->text_finalScore->SetText(FText::FromString(FString::Printf(TEXT("%d"))));
		rankSlot->text_finalKillScore->SetText(FText::FromString(FString::Printf(TEXT("%d"))));
		rankSlot->text_finalDeaths->SetText(FText::FromString(FString::Printf(TEXT("%d"))));
		sbox_RankList->AddChild(rankSlot);
	}
}
/*
void UGameOverWidget::ListUpSlots()
{
	FString playerLastList;
	if(GetWorld()->GetGameState() != nullptr)
	{
		ABoxGameStateBase* gs = Cast<ABoxGameStateBase>(GetWorld()->GetGameState());
		for(const auto& ps : gs->GetGoPlayerListByScore())
		{
			
		}
	}
}
*/
