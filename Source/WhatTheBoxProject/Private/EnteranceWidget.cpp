// Fill out your copyright notice in the Description page of Project Settings.


#include "EnteranceWidget.h"

#include "SearchWidget.h"
#include "Components/TextBlock.h"
#include "Components/Button.h"
#include "SessionSlotWidget.h"
#include "Components/ScrollBox.h"
#include "Components/WidgetSwitcher.h"


void UEnteranceWidget::NativeConstruct()
{
	Super::NativeConstruct();

	btn_Play->OnClicked.AddDynamic(this, &UEnteranceWidget::ClickPlay);
}

void UEnteranceWidget::ClickPlay()
{
	widgetSwitcher->SetActiveWidgetIndex(1);
}

void UEnteranceWidget::AddRoomSlot(FString roomName, int32 gamePlayTime, int32 currentPlayers, int32 maxPlayers, int32 ping)
{
	USessionSlotWidget* searchSlotListWidget = CreateWidget<USessionSlotWidget>(this, searchListSlot);
	if(searchSlotListWidget != nullptr)
	{
		searchSlotListWidget->text_RoomName->SetText(FText::FromString(roomName));
		searchSlotListWidget->text_GameMode->SetText(FText::FromString(TEXT("DeathMatch")));
		searchSlotListWidget->text_MemberCount->SetText(FText::FromString(FString::Printf(TEXT("%d / %d"), currentPlayers, maxPlayers)));
		searchSlotListWidget->text_GameTime->SetText(FText::FromString(FString::Printf(TEXT(" % d"), gamePlayTime)));
		searchSlotListWidget->text_Description->SetText(FText::AsNumber(ping));
		sbox_RoomList->AddChild(searchSlotListWidget);
	}
}
