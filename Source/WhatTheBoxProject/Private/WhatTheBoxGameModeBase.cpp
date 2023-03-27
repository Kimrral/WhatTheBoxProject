// Fill out your copyright notice in the Description page of Project Settings.


#include "WhatTheBoxGameModeBase.h"
#include "../WhatTheBoxProjectCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "BoxMainWidget.h"

AWhatTheBoxGameModeBase::AWhatTheBoxGameModeBase()
{
}

void AWhatTheBoxGameModeBase::BeginPlay()
{
	GetWorldTimerManager().SetTimer(PlayTimeCount, this, &AWhatTheBoxGameModeBase::GameStartCountDown, 1.0f, true, 0);
	
	// 메인 위젯
	Main_UI = CreateWidget<UBoxMainWidget>(GetWorld(), MainWidget);
	Main_UI->AddToViewport();
}

void AWhatTheBoxGameModeBase::GameStartCountDown()
{
	// 게임시간이 0초가 아니라면 1초 줄인다.
	if (GameTimeSec > 0)
	{
		//UE_LOG(LogTemp, Warning, TEXT("F!!!!!"));
		if (Main_UI != nullptr)
		{
			Main_UI->PrintRemainingTime();
		}
		GameTimeSec--;
		// 만약 0초가 되면 1분을 줄이고, 다시 59초로 초기화한다.
		if (GameTimeSec == 0)
		{
			GameTimeMin--;
			GameTimeSec = 59;
		}
	}
	// 만약 0초가 되면 결과창을 띄운다.
	else if (GameTimeSec == 0 && GameTimeMin == 0)
	{
		// 타이머를 종료
		GetWorldTimerManager().ClearTimer(PlayTimeCount);
		if (Main_UI != nullptr)
		{
		//	Main_UI->
		}
		ShowResultUI();
	}
}

void AWhatTheBoxGameModeBase::ShowResultUI()
{
	// 마우스 커서를 보이게 한다.
	APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
}
