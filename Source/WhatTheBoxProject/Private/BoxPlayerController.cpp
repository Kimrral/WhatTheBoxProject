// Fill out your copyright notice in the Description page of Project Settings.


#include "BoxPlayerController.h"
#include "BoxMainWidget.h"
#include "WhatTheBoxGameModeBase.h"
#include "GameFramework/PlayerStart.h"
#include "EngineUtils.h"
#include "Kismet/GameplayStatics.h"


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

void ABoxPlayerController::Respawn(AWhatTheBoxProjectCharacter* player)
{
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), playerStartFactory, outActors);
	int32 rand = FMath::RandRange(0, outActors.Num()-1);
	auto randStart = outActors[rand];
	
	if(HasAuthority()&&player!=nullptr)
	{
		GM=Cast<AWhatTheBoxGameModeBase>(GetWorld()->GetAuthGameMode());
		if(GM!=nullptr)
		{
			
			GM->RestartPlayerAtPlayerStart(this, randStart);
		}
	}


}
