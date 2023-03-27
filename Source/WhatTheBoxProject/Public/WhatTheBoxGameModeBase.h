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

	//���� ���� �κ�
public:
	// ���� ����
	UPROPERTY(BlueprintReadWrite, Category = "Widget")
		class UBoxMainWidget* Main_UI;

	UPROPERTY(EditAnywhere)
	TSubclassOf<class UBoxMainWidget> MainWidget;

	// �÷��̾�
	UPROPERTY(BlueprintReadWrite, Category = "Player")
		class AWhatTheBoxProjectCharacter* Player;

	// ���� ��, ��� ����
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Widget")
		TSubclassOf<class UUserWidget> ResultWidget;
	UPROPERTY()
	class UUserWidget* Result_UI;


	// �ð� ��
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int32 GameTimeSec = 1;
	// �ð� ��
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int32 GameTimeMin = 5;




	//�Լ� �κ�
public:
	// ���� ���۽�, 5�� ī��Ʈ �ٿ�
	void GameStartCountDown();
	
	//���� �ð� ������ ���â �˾�
	void ShowResultUI();

	FTimerHandle TimerHandle;
	FTimerHandle PlayTimeCount;
};
