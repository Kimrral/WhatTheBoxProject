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
	if (GameTime > 0)
	{
		GameTime--;
	}
	else
	{
		// 게임시간이 0초가 되면 타이머를 멈춘다.
		GetWorldTimerManager().ClearTimer(PlayTimeCount);
	}
}
