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

	// 메인 위젯
	Main_UI = CreateWidget<UBoxMainWidget>(GetWorld(), MainWidget);
	// 메인위젯을 플레이어의 화면에 띄운다.
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
			// 만약 0분이 되면 게임을 종료한다.
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
	// 로그출력
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
		// 결과 위젯을 띄운다.
		GameOver_UI->AddToViewport();

		// 마우스커서 보이게하기
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

