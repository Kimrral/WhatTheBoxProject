// Fill out your copyright notice in the Description page of Project Settings.


#include "BoxPlayerController.h"
#include "BoxMainWidget.h"
#include "WhatTheBoxGameModeBase.h"


void ABoxPlayerController::BeginPlay()
{
	Super::BeginPlay();

	if (mainWidget != nullptr && IsLocalController())
	{
		UBoxMainWidget* MainUI = CreateWidget<UBoxMainWidget>(this, mainWidget);

		if (MainUI != nullptr)
		{
			MainUI->AddToViewport();
		}
	}

}
