// Fill out your copyright notice in the Description page of Project Settings.


#include "WhatTheBoxGameModeBase.h"

AWhatTheBoxGameModeBase::AWhatTheBoxGameModeBase()
{
}

void AWhatTheBoxGameModeBase::BeginPlay()
{
}

void AWhatTheBoxGameModeBase::GameStartCountDown()
{
	// ���ӽð��� 0�ʰ� �ƴ϶�� 1�� ���δ�.
	if (GameTime > 0)
	{
		GameTime--;
	}
	else
	{
		// ���ӽð��� 0�ʰ� �Ǹ� Ÿ�̸Ӹ� �����.
		GetWorldTimerManager().ClearTimer(PlayTimeCount);
	}
}
