// Fill out your copyright notice in the Description page of Project Settings.


#include "BoxMainWidget.h"
#include "WhatTheBoxGameModeBase.h"
#include "Kismet/GameplayStatics.h"
#include "Components/TextBlock.h"
#include "../WhatTheBoxProjectCharacter.h"

void UBoxMainWidget::NativeConstruct()
{
	Super::NativeConstruct();

	// 게임모드
	GM = Cast<AWhatTheBoxGameModeBase>(GetWorld()->GetAuthGameMode());
	// 플레이어
	Player = Cast<AWhatTheBoxProjectCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));

	
}

void UBoxMainWidget::PrintRemainingTime()
{
	// 남은 시간을 텍스트로 출력한다.
	if (GM != nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("Fire!!!!!"));
		TXT_GameTimeSec->SetText(FText::FromString(FString::FromInt(GM->GameTimeSec)));
		TXT_GameTimeMin->SetText(FText::FromString(FString::FromInt(GM->GameTimeMin)));
	}
	
}

void UBoxMainWidget::PrintKillLog(FString Killer, FString Victim)
{
	// 킬로그를 출력한다.
	TXT_KillLog->SetText(FText::FromString(Killer + " killed " + Victim));
}

// 채팅인풋에 입력시 채팅로그에 출력
void UBoxMainWidget::PrintChatLog(FString Chat)
{
	// 채팅로그를 출력한다.
	TXT_ChatLog->SetText(FText::FromString(Chat));
}
