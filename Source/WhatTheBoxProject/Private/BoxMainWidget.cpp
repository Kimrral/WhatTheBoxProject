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
#include "BoxPlayerState.h"
#include "BoxGameStateBase.h"
#include "WTBoxGameInstance.h"

void UBoxMainWidget::NativeConstruct()
{
	Super::NativeConstruct();

	// 게임모드
	GM = Cast<AWhatTheBoxGameModeBase>(GetWorld()->GetAuthGameMode());

	// 게임타이머액터
	inGameTimer = Cast<ATimerActor>(UGameplayStatics::GetActorOfClass(GetWorld(), ATimerActor::StaticClass()));

	// 플레이어
	Player = Cast<AWhatTheBoxProjectCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));

	gameInstance = Cast<UWTBoxGameInstance>(GetGameInstance());


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

	// 플레이어 점수
	FString playerList;

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
			//text_PlayerID->SetText(FText::FromString(playerList));
			//text_PlayerScore->SetText(FText::FromString(playerList));		
	}	
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
	//ABoxGameStateBase 에 있는 GetPlayerListByScore() 함수 불러오기
	ABoxGameStateBase* GS = Cast<ABoxGameStateBase>(GetWorld()->GetGameState());
	TArray<APlayerState*> PlayerList = GS->GetPlayerListByScore();


}

void UBoxMainWidget::PrintKillLog(FString Killer, FString Victim)
{
	// 킬로그를 출력한다.
	//TXT_KillLog->SetText(FText::FromString(Killer + " killed " + Victim));
}

// 채팅인풋에 입력시 채팅로그에 출력
void UBoxMainWidget::PrintChatLog(FString Chat)
{

}

void UBoxMainWidget::OnChatInputEnter()
{

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
