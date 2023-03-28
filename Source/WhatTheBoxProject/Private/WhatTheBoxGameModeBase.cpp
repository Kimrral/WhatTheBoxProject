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
	if (GameTimeSec > 0 || GameTimeMin > 0)
	{
		//UE_LOG(LogTemp, Warning, TEXT("F!!!!!"));
		// ���� 0�ʰ� �Ǹ� 1���� ���̰�, �ٽ� 59�ʷ� �ʱ�ȭ�Ѵ�.
		if (GameTimeSec == 0)
		{
			GameTimeMin--;
			GameTimeSec = 59;
		}
		else
		{
			GameTimeSec--;
		}
		if (Main_UI != nullptr)
		{
			Main_UI->PrintRemainingTime();
		}
	}
	else
	{
		ShowResultUI();
	}
}

void AWhatTheBoxGameModeBase::ShowResultUI()
{
	// Ÿ�̸Ӹ� �����Ų��.
	GetWorld()->GetTimerManager().ClearTimer(PlayTimeCount);

	// ���콺 Ŀ���� ���̰� �Ѵ�.
	APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	// �÷��̾ �����.
	PlayerController->SetCinematicMode(true, false, false, true, true);

}
