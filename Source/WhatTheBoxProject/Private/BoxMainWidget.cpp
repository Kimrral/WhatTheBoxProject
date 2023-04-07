// Fill out your copyright notice in the Description page of Project Settings.


#include "BoxMainWidget.h"
#include "WhatTheBoxGameModeBase.h"
#include "Kismet/GameplayStatics.h"
#include "Components/TextBlock.h"
#include "Components/EditableTextBox.h"
#include "Components/ScrollBox.h"
#include "../WhatTheBoxProjectCharacter.h"
#include "BoxGameMode.h"
#include "Net/UnrealNetwork.h"
#include "TimerActor.h"
#include "GameFrameWork/PlayerState.h"
#include "GameFrameWork/GameStateBase.h"
#include "BoxPlayerState.h"
#include "BoxGameStateBase.h"
#include "WTBoxGameInstance.h"
#include "BoxPlayerController.h"
#include "EngineUtils.h"


void UBoxMainWidget::NativeConstruct()
{
	Super::NativeConstruct();

	// ���Ӹ��
	GM = Cast<AWhatTheBoxGameModeBase>(GetWorld()->GetAuthGameMode());

	// ����Ÿ�̸Ӿ���
	inGameTimer = Cast<ATimerActor>(UGameplayStatics::GetActorOfClass(GetWorld(), ATimerActor::StaticClass()));

	// �÷��̾�
	Player = Cast<AWhatTheBoxProjectCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));


	gameInstance = Cast<UWTBoxGameInstance>(GetGameInstance());



	// �÷��̾� ��Ʈ�ѷ�
	PC = Cast<ABoxPlayerController>(GetOwningLocalPlayer()->GetPlayerController(GetWorld()));

	// ��ŷ ������� �迭
	textblockRankIdArray = { TXT_RankID1, TXT_RankID2, TXT_RankID3, TXT_RankID4 };
	textblockRankScoreArray = { TXT_RankScore1, TXT_RankScore2, TXT_RankScore3, TXT_RankScore4 };
	tempScoreArray = { tempScore1, tempScore2, tempScore3, tempScore4 };

}

void UBoxMainWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	/*UE_LOG(LogTemp, Warning, TEXT("%s"), GetWorld()->GetAuthGameMode() != nullptr ? *FString("HAS") : *FString("None"));*/

	// 	AWhatTheBoxGameModeBase* gm = Cast< AWhatTheBoxGameModeBase>(GetWorld()->GetAuthGameMode());
	ABoxGameStateBase* gs = Cast<ABoxGameStateBase>(GetWorld()->GetGameState());

	if (inGameTimer != nullptr && this != nullptr)
	{
		inGameTimer->Server_UpdateTimerUI();
	}


	// �÷��̾� ����
	FString playerList;
//	RankingRefresh();

	if (GetWorld()->GetGameState() != nullptr)
	{
		ABoxGameStateBase* GS = Cast<ABoxGameStateBase>(GetWorld()->GetGameState());
		for (const auto& ps : GS->GetPlayerListByScore())
		{

			playerName = ps->GetPlayerName();
			playerScore = ps->GetScore();
			playerList.Append(FString::Printf(TEXT("%s_____________: %d\n"), *playerName, playerScore));
			UE_LOG(LogTemp, Warning, TEXT("%s : %d"), *playerName, playerScore);
		}		
			text_PlayerID->SetText(FText::FromString(playerList));
			//text_PlayerScore->SetText(FText::FromString(playerList));		
	}	





void UBoxMainWidget::PrintRemainingTime(int32 min, int32 sec)
{
	// ���� �ð��� �ؽ�Ʈ�� ����Ѵ�.

	TXT_GameTimeMin->SetText(FText::AsNumber(min));
	TXT_GameTimeSec->SetText(FText::AsNumber(sec));

	if (sec < 10)
	{
		TXT_GameTimeSec->SetText(FText::FromString("0" + FString::FromInt(sec)));
	}

// 	if (inGameTimer != nullptr)
// 	{
// 		
// 		// ���� GameTimeSec�� 10���� ������ GameTimeSec �տ� 0�� �ٿ��ش�.
// 		if (inGameTimer->GameTimeSec < 10)
// 		{
// 			TXT_GameTimeSec->SetText(FText::FromString("0" + FString::FromInt(inGameTimer->GameTimeSec)));
// 		}
// 	}

}

void UBoxMainWidget::RankingRefresh()
{
#pragma region Rank
// 	//ABoxGameStateBase �� �ִ� GetPlayerListByScore() �Լ� �ҷ�����
// 	ABoxGameStateBase* GS = Cast<ABoxGameStateBase>(GetWorld()->GetGameState());
// 	TArray<APlayerState*> PlayerList = GS->GetPlayerListByScore();
// 
// 	// ���ĵ� ������� ��ŷǥ�� ���
// 	for (int i = 0; i < PlayerList.Num(); i++)
// 	{
// 		ABoxPlayerState* PS = Cast<ABoxPlayerState>(PlayerList[i]);
// 		FString PlayerName = PS->GetPlayerName();
// 		int32 PlayerScore = PS->GetScore();
// 		switch (i)
// 		{
// 		case 0:
// 			TXT_RankID1->SetText(FText::FromString(PlayerName + " : " + FString::FromInt(PlayerScore)));
// 			break;
// 		case 1:
// 			TXT_RankID2->SetText(FText::FromString(PlayerName + " : " + FString::FromInt(PlayerScore)));
// 			break;
// 		case 2:
// 			TXT_RankID3->SetText(FText::FromString(PlayerName + " : " + FString::FromInt(PlayerScore)));
// 			break;
// 		case 3:
// 			TXT_RankID4->SetText(FText::FromString(PlayerName + " : " + FString::FromInt(PlayerScore)));
// 			break;
// 		default:
// 			break;
// 		}
// 	}
#pragma endregion

#pragma region AnotherRank
	// playerstate array ��������
	auto playerStateArray = GetWorld()->GetGameState()->PlayerArray;

	playerStateArray.Sort([](const APlayerState& A, const APlayerState& B)
		{
			return A.GetScore() > B.GetScore();
		});

	// ���ĵ� ������� ��ŷǥ�� ���
	for (int i = 0; i < playerStateArray.Num(); i++)
	{
		textblockRankIdArray[i]->SetVisibility(ESlateVisibility::Visible);
		textblockRankIdArray[i]->SetText(FText::FromString(playerStateArray[i]->GetPlayerName()));

		textblockRankScoreArray[i]->SetVisibility(ESlateVisibility::Visible);
		if (tempScoreArray[i] < playerStateArray[i]->GetScore())
		{
			textblockRankScoreArray[i]->SetText(FText::AsNumber(tempScoreArray[i]));
		}
	}
	if (!playerStateArray.IsEmpty())
	{
		winnerID = playerStateArray[0]->GetPlayerName();
	}
#pragma endregion
}

void UBoxMainWidget::PrintKillLog(FString Killer, FString Victim)
{
	// ų�α׸� ����Ѵ�.
	//TXT_KillLog->SetText(FText::FromString(Killer + " killed " + Victim));
}

// ä����ǲ�� �Է½� ä�÷α׿� ���
void UBoxMainWidget::PrintChatLog(FString Chat)
{

}

void UBoxMainWidget::OnChatInputEnter()
{

}


void UBoxMainWidget::ResetScoreBeforeGameEnd()
{
	tempScore1 = 0;
	tempScore2 = 0;
	tempScore3 = 0;
	tempScore4 = 0;
}

void UBoxMainWidget::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	// Replicate GM variable
	DOREPLIFETIME(UBoxMainWidget,inGameTimer);
}

//void UBoxMainWidget::UpdateKillLog(const TArray<FString>& KillLog)
//{
//	FString KillLogText;
//	for (const FString& KillMessage : KillLog)
//	{
//		KillLogText += KillMessage + TEXT("\n");
//	}
//	TXT_KillLog->SetText(FText::FromString(KillLogText));
//}
