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
	// 게임시간이 0초가 아니라면 1초 줄인다.
	if (GameTimeSec > 0)
	{
		GameTimeSec--;
		// 만약 0초가 되면 1분을 줄인다.
		if (GameTimeSec == 0)
		{
			GameTimeMin--;
		}
	}
	// 만약 0초가 되면 결과창을 띄운다.
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
