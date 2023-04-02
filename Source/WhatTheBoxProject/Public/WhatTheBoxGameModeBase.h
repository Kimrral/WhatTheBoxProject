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
	UPROPERTY(BlueprintReadWrite, Category = "Widget" , Replicated)
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
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Replicated)
		int32 GameTimeSec = 1;
	// �ð� ��
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Replicated)
		int32 GameTimeMin = 5;

	// ���� ������Ʈ �ð�
// 	UPROPERTY(Replicated)
// 	float RemainingTime;


	//�Լ� �κ�
public:
	// ���� ���۽�, 5�� ī��Ʈ �ٿ�
	void GameStartCountDown();
	
	//���� �ð� ������ ���â �˾�
	void ShowResultUI();

	UFUNCTION(Server, UnReliable, WithValidation)
	void Server_GameStartCountDown();

	UFUNCTION(NetMulticast, UnReliable)
	void Multicast_UpdateTimerUI();

	// GetLifetimeReplicatedprops
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	UPROPERTY(Replicated)
	FTimerHandle TimerHandle;
	FTimerHandle PlayTimeCount;
};
