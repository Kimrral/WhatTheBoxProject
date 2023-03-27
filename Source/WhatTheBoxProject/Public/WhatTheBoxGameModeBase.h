// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "WhatTheBoxGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class WHATTHEBOXPROJECT_API AWhatTheBoxGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
	
public:
	AWhatTheBoxGameModeBase();


public:
	virtual void BeginPlay() override;

	//전방 선언 부분
public:
	// 메인 위젯
	UPROPERTY(BlueprintReadWrite, Category = "Widget")
		class UBoxMainWidget* Main_UI;

	UPROPERTY(EditAnywhere)
	TSubclassOf<class UBoxMainWidget> MainWidget;

	// 플레이어
	UPROPERTY(BlueprintReadWrite, Category = "Player")
		class AWhatTheBoxProjectCharacter* Player;

	// 게임 끝, 결과 위젯
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Widget")
		TSubclassOf<class UUserWidget> ResultWidget;
	UPROPERTY()
	class UUserWidget* Result_UI;


	// 시간 초
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int32 GameTimeSec = 1;
	// 시간 분
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int32 GameTimeMin = 5;




	//함수 부분
public:
	// 게임 시작시, 5분 카운트 다운
	void GameStartCountDown();
	
	//게임 시간 끝나면 결과창 팝업
	void ShowResultUI();

	FTimerHandle TimerHandle;
	FTimerHandle PlayTimeCount;
};
