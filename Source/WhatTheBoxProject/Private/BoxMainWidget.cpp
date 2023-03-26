// Fill out your copyright notice in the Description page of Project Settings.


#include "BoxMainWidget.h"
#include "WhatTheBoxGameModeBase.h"
#include "Kismet/GameplayStatics.h"
#include "Components/TextBlock.h"

void UBoxMainWidget::NativeConstruct()
{
	Super::NativeConstruct();

	// 게임모드
	GM = Cast<AWhatTheBoxGameModeBase>(GetWorld()->GetAuthGameMode());
	// 플레이어
//	Player = Cast<AWhatTheBoxProjectCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
}

void UBoxMainWidget::PrintRemainingTime()
{
	// 만약 게임모드가 존재하면
	if (GM != nullptr)
	{
		// 남은 시간 텍스트를 출력한다.
		//TXT_GameTimeSec->SetText(FText::FromString(FString::FromInt(GM->GameTimeSec)));
		//TXT_GameTimeMin->SetText(FText::FromString(FString::FromInt(GM->GameTimeMin)));
	}
}

void UBoxMainWidget::PrintKillLog(FString Killer, FString Victim)
{
	// 킬로그를 출력한다.
	//TXT_KillLog->SetText(FText::FromString(Killer + " killed " + Victim));
}
