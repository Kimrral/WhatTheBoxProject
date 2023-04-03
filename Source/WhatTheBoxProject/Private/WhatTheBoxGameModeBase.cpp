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
	
	// ���� ����
	Main_UI = CreateWidget<UBoxMainWidget>(GetWorld(), MainWidget);
	Main_UI->AddToViewport();
}

void AWhatTheBoxGameModeBase::GameStartCountDown()
{
	if (GetLocalRole() == ROLE_Authority)
	{
		// ���ӽð��� 0�ʰ� �ƴ϶�� 1�� ���δ�.
		if (GameTimeSec > 0 || GameTimeMin > 0)
		{
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
			Multicast_UpdateTimerUI();
		}
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
	// �α����
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

