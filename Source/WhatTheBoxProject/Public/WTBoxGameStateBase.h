// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "WTBoxGameStateBase.generated.h"

/**
 * 
 */
UCLASS()
class WHATTHEBOXPROJECT_API AWTBoxGameStateBase : public AGameStateBase
{
	GENERATED_BODY()
public:
	//�÷��̾� ������� ȭ�� ���� ��ܿ� ����
	TArray<class APlayerState*> GetPlayerListByScore();

	//�÷��̰� ������ ���� ������ ������� ����


};
