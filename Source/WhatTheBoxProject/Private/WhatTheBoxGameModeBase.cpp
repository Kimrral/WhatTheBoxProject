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
	
	// ���� ����
	Main_UI = CreateWidget<UBoxMainWidget>(GetWorld(), MainWidget);
	Main_UI->AddToViewport();
}

void AWhatTheBoxGameModeBase::GameStartCountDown()
{
	// ���ӽð��� 0�ʰ� �ƴ϶�� 1�� ���δ�.
	if (GameTimeSec > 0)
	{
		//UE_LOG(LogTemp, Warning, TEXT("F!!!!!"));
		if (Main_UI != nullptr)
		{
			Main_UI->PrintRemainingTime();
		}
		GameTimeSec--;
		// ���� 0�ʰ� �Ǹ� 1���� ���̰�, �ٽ� 59�ʷ� �ʱ�ȭ�Ѵ�.
		if (GameTimeSec == 0)
		{
			GameTimeMin--;
			GameTimeSec = 59;
		}
	}
	// ���� 0�ʰ� �Ǹ� ���â�� ����.
	else if (GameTimeSec == 0 && GameTimeMin == 0)
	{
		// Ÿ�̸Ӹ� ����
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
	// ���콺 Ŀ���� ���̰� �Ѵ�.
	APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
}
