// Fill out your copyright notice in the Description page of Project Settings.


#include "SessionSlotWidget.h"

#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "WTBoxGameInstance.h"

void USessionSlotWidget::NativeConstruct()
{
	Super::NativeConstruct();

	gameInstance = Cast<UWTBoxGameInstance>(GetGameInstance());
	btn_JoinRoom->OnClicked.AddDynamic(this, &USessionSlotWidget::ClickJoinRoom);
}

void USessionSlotWidget::ClickJoinRoom()
{
	//������ ����
	if(gameInstance != nullptr)
	{
		gameInstance->JoinwtbSessions(index);
	}
}
