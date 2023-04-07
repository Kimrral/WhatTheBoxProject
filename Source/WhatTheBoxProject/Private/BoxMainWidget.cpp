// Fill out your copyright notice in the Description page of Project Settings.


#include "BoxMainWidget.h"
#include "WhatTheBoxGameModeBase.h"
#include "Kismet/GameplayStatics.h"
#include "Components/TextBlock.h"
#include "Components/EditableTextBox.h"
#include "Components/VerticalBox.h"
#include "../WhatTheBoxProjectCharacter.h"
#include "BoxGameMode.h"
#include "Net/UnrealNetwork.h"
#include "TimerActor.h"
#include "GameFrameWork/PlayerState.h"
#include "GameFrameWork/GameStateBase.h"
#include "BoxPlayerState.h"
#include "BoxGameStateBase.h"
#include "BoxPlayerController.h"
#include "EngineUtils.h"

void UBoxMainWidget::NativeConstruct()
{
	Super::NativeConstruct();

	// 게임모드
	GM = Cast<AWhatTheBoxGameModeBase>(GetWorld()->GetAuthGameMode());

	// 게임타이머액터
	inGameTimer = Cast<ATimerActor>(UGameplayStatics::GetActorOfClass(GetWorld(), ATimerActor::StaticClass()));

	// 플레이어
	Player = Cast<AWhatTheBoxProjectCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));

	// 플레이어 컨트롤러
	PC = Cast<ABoxPlayerController>(GetOwningLocalPlayer()->GetPlayerController(GetWorld()));

	// 랭킹 구성요소 배열
	textblockRankIdArray = { TXT_RankID1, TXT_RankID2, TXT_RankID3, TXT_RankID4 };
	textblockRankScoreArray = { TXT_RankScore1, TXT_RankScore2, TXT_RankScore3, TXT_RankScore4 };
	tempScoreArray = { tempScore1, tempScore2, tempScore3, tempScore4 };
}

void UBoxMainWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	/*UE_LOG(LogTemp, Warning, TEXT("%s"), GetWorld()->GetAuthGameMode() != nullptr ? *FString("HAS") : *FString("None"));*/

	// 	AWhatTheBoxGameModeBase* gm = Cast< AWhatTheBoxGameModeBase>(GetWorld()->GetAuthGameMode());

	if (inGameTimer != nullptr && this != nullptr)
	{
		inGameTimer->Server_UpdateTimerUI();
	}


	// 플레이어 점수
	FString playerList;
//	RankingRefresh();
#pragma region regionName
	if (GetWorld()->GetGameState() != nullptr)
	{
		ABoxGameStateBase* GS = Cast<ABoxGameStateBase>(GetWorld()->GetGameState());
		for (const auto& ps : GS->GetPlayerListByScore())
		{
			FString playerName = ps->GetPlayerName();
			int32 playerScore = ps->GetScore();
			playerList.Append(FString::Printf(TEXT("%s : %d\n"), *playerName, playerScore));
		}

		TXT_RankID1->SetText(FText::FromString(playerList));
	}
#pragma endregion regionName
}

void UBoxMainWidget::PrintRemainingTime(int32 min, int32 sec)
{
	// 남은 시간을 텍스트로 출력한다.

	TXT_GameTimeMin->SetText(FText::AsNumber(min));
	TXT_GameTimeSec->SetText(FText::AsNumber(sec));

	if (sec < 10)
	{
		TXT_GameTimeSec->SetText(FText::FromString("0" + FString::FromInt(sec)));
	}

// 	if (inGameTimer != nullptr)
// 	{
// 		
// 		// 만약 GameTimeSec이 10보다 적으면 GameTimeSec 앞에 0을 붙여준다.
// 		if (inGameTimer->GameTimeSec < 10)
// 		{
// 			TXT_GameTimeSec->SetText(FText::FromString("0" + FString::FromInt(inGameTimer->GameTimeSec)));
// 		}
// 	}

}

void UBoxMainWidget::RankingRefresh()
{
#pragma region Rank
// 	//ABoxGameStateBase 에 있는 GetPlayerListByScore() 함수 불러오기
// 	ABoxGameStateBase* GS = Cast<ABoxGameStateBase>(GetWorld()->GetGameState());
// 	TArray<APlayerState*> PlayerList = GS->GetPlayerListByScore();
// 
// 	// 정렬된 순서대로 랭킹표에 출력
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
	// playerstate array 가져오기
	auto playerStateArray = GetWorld()->GetGameState()->PlayerArray;

	playerStateArray.Sort([](const APlayerState& A, const APlayerState& B)
		{
			return A.GetScore() > B.GetScore();
		});

	// 정렬된 순서대로 랭킹표에 출력
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
	// 킬로그를 출력한다.
	TXT_KillLog->SetText(FText::FromString(Killer + " killed " + Victim));
}

// 채팅인풋에 입력시 채팅로그에 출력
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
