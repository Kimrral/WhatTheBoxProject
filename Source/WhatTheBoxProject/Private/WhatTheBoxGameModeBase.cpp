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
	if (GameTimeSec > 0)
	{
		GameTimeSec--;
		// ���� 0�ʰ� �Ǹ� 1���� ���δ�.
		if (GameTimeSec == 0)
		{
			GameTimeMin--;
		}
	}
	// ���� 0�ʰ� �Ǹ� ���â�� ����.
	else if (GameTimeSec == 0 && GameTimeMin == 0)
	{
		if (Main_UI != nullptr)
		{
			//Main_UI->RemoveFromViewport();
		}
		ShowResultUI();
	}
}

void AWhatTheBoxGameModeBase::ShowResultUI()
{
	
}
