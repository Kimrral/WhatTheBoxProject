// Fill out your copyright notice in the Description page of Project Settings.


#include "TimerActor.h"
#include "WhatTheBoxGameModeBase.h"
#include "BoxMainWidget.h"
#include "Components/TextBlock.h"
#include "Net/UnrealNetwork.h"
#include "../WhatTheBoxProjectCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "GameOverWidget.h"

// Sets default values
ATimerActor::ATimerActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
}

// Called when the game starts or when spawned
void ATimerActor::BeginPlay()
{
	Super::BeginPlay();

	GetWorldTimerManager().SetTimer(PlayTimeCount, this, &ATimerActor::GameStartCountDown, 1.0f, true, 0);

	// ���� ����
	Main_UI = CreateWidget<UBoxMainWidget>(GetWorld(), MainWidget);
	// ���������� �÷��̾��� ȭ�鿡 ����.
	Main_UI->AddToViewport();
}

// Called every frame
void ATimerActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ATimerActor::GameStartCountDown()
{
	if (HasAuthority())
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
			// ���� 0���� �Ǹ� ������ �����Ѵ�.
			if (GameTimeMin == 0 && GameTimeSec == 0)
			{
				UE_LOG( LogTemp, Warning, TEXT("Game Over") );
				Server_ResultUI();
			}
		}
	}
}

void ATimerActor::Server_GameStartCountDown_Implementation()
{
	if (GetLocalRole() == ROLE_Authority)
	{
		GetWorldTimerManager().SetTimer(TimerHandle, this, &ATimerActor::GameStartCountDown, 1.0f, true);
	}
}

bool ATimerActor::Server_GameStartCountDown_Validate()
{
	return true;
}

void ATimerActor::Server_UpdateTimerUI_Implementation()
{
	Multicast_UpdateTimerUI();
}

void ATimerActor::Multicast_UpdateTimerUI_Implementation()
{
	// �α����
//	GEngine->AddOnScreenDebugMessage(-1, 3, FColor::Red, FString("ticktock!"), true, FVector2D(1.2f));
//	UE_LOG(LogTemp, Warning, TEXT("qwer"));
	if (Main_UI != nullptr)
	{
		Main_UI->PrintRemainingTime(GameTimeMin, GameTimeSec);
	}
}

void ATimerActor::Server_ResultUI_Implementation()
{
	Multicast_ResultUI();
}

void ATimerActor::Multicast_ResultUI_Implementation()
{
	GameOver_UI = CreateWidget<UGameOverWidget>(GetWorld(), GameOverWidget);

	if (GameOver_UI != nullptr)
	{
		// ��� ������ ����.
		GameOver_UI->AddToViewport();

		// ���콺Ŀ�� ���̰��ϱ�
		APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
		PlayerController->bShowMouseCursor = true;
	}

}

void ATimerActor::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	DOREPLIFETIME(ATimerActor, GameTimeSec);
	DOREPLIFETIME(ATimerActor, GameTimeMin);
	DOREPLIFETIME(ATimerActor, Main_UI);
	DOREPLIFETIME(ATimerActor, GameOver_UI)
}

