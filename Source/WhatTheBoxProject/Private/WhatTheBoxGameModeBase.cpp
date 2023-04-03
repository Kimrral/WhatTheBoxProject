// Fill out your copyright notice in the Description page of Project Settings.


#include "WhatTheBoxGameModeBase.h"
#include "../WhatTheBoxProjectCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "BoxMainWidget.h"
#include "TimerManager.h"
#include "Components/TextBlock.h"
#include "Net/UnrealNetwork.h"
#include "DrawDebugHelpers.h"

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
	if (GetLocalRole() == ROLE_Authority)
	{
		// 게임시간이 0초가 아니라면 1초 줄인다.
		if (GameTimeSec > 0 || GameTimeMin > 0)
		{
			// 만약 0초가 되면 1분을 줄이고, 다시 59초로 초기화한다.
			if (GameTimeSec == 0)
			{
				GameTimeMin--;
				GameTimeSec = 59;
			}
			else
			{
				GameTimeSec--;
			}
			Multicast_UpdateTimerUI();
		}
	}
}

void AWhatTheBoxGameModeBase::ShowResultUI()
{
	// 타이머를 종료시킨다.
	GetWorld()->GetTimerManager().ClearTimer(PlayTimeCount);

	// 마우스 커서를 보이게 한다.
	APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	// 플레이어를 멈춘다.
	PlayerController->SetCinematicMode(true, false, false, true, true);

}

void AWhatTheBoxGameModeBase::Server_GameStartCountDown_Implementation()
{
	if (GetLocalRole() == ROLE_Authority)
	{
		GetWorldTimerManager().SetTimer(TimerHandle, this, &AWhatTheBoxGameModeBase::GameStartCountDown, 1.0f, true);
	}
}

bool AWhatTheBoxGameModeBase::Server_GameStartCountDown_Validate()
{
	return true;
}

void AWhatTheBoxGameModeBase::Multicast_UpdateTimerUI_Implementation()
{
	// 로그출력
	GEngine->AddOnScreenDebugMessage(-1, 3, FColor::Red, FString("ticktock!"), true, FVector2D(1.2f));
	UE_LOG(LogTemp, Warning, TEXT("qwer"));
	if (Main_UI != nullptr)
	{
		Main_UI->PrintRemainingTime();
	}
}

void AWhatTheBoxGameModeBase::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AWhatTheBoxGameModeBase, GameTimeSec);
	DOREPLIFETIME(AWhatTheBoxGameModeBase, GameTimeMin);
	DOREPLIFETIME(AWhatTheBoxGameModeBase, Main_UI);
}

