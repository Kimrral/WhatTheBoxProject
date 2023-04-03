// Fill out your copyright notice in the Description page of Project Settings.


#include "SessionSlotWidget.h"

#include "Components/Button.h"
#include "Components/TextBlock.h"

void USessionSlotWidget::NativeConstruct()
{
	Super::NativeConstruct();

	text_RoomName->SetText(FText::FromString(""));
	text_GameMode->SetText(FText::FromString(""));
	text_GameTime->SetText(FText::FromString(""));
	text_MemberCount->SetText(FText::FromString(""));
	text_Description->SetText(FText::FromString(""));

	btn_JoinRoom->OnClicked.AddDynamic(this, &USessionSlotWidget::ClickJoinRoom);
}

void USessionSlotWidget::ClickJoinRoom()
{
	//방으로 입장
}
