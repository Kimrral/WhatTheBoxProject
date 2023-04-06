// Fill out your copyright notice in the Description page of Project Settings.


#include "BoxPlayerController.h"
#include "BoxMainWidget.h"
#include "WhatTheBoxGameModeBase.h"
#include "WTBoxGameInstance.h"
#include "BoxPlayerState.h"
#include "GameFrameWork/PlayerState.h"


ABoxPlayerController::ABoxPlayerController()
{
}

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
	BoxInstance = Cast<UWTBoxGameInstance>(GetGameInstance());
	if (BoxInstance != nullptr)
	{
		ServerSetName(BoxInstance->sessionID.ToString());
	}

}

void ABoxPlayerController::Tick(float DeltaSeconds)
{

}

void ABoxPlayerController::ServerSetName_Implementation(const FString& name)
{
	GetPlayerState<ABoxPlayerState>()->SetPlayerName(name);
}
