// Fill out your copyright notice in the Description page of Project Settings.


#include "EnteranceWidget.h"

#include "SearchWidget.h"
#include "Components/TextBlock.h"
#include "Components/Slider.h"
#include "Components/EditableText.h"
#include "Components/Button.h"
#include "SessionSlotWidget.h"
#include "Components/ScrollBox.h"
#include "Components/WidgetSwitcher.h"
#include "WTBoxGameInstance.h"


void UEnteranceWidget::NativeConstruct()
{
	Super::NativeConstruct();

	btn_Play->OnClicked.AddDynamic(this, &UEnteranceWidget::ClickPlay);
	editText_RoomName->SetText(FText::FromString(""));
	text_MatchDurations->SetText(FText::FromString(""));
	text_MaxPlayersCount->SetText(FText::FromString(""));
	slider_MatchDurations->OnValueChanged.AddDynamic(this, &UEnteranceWidget::OnMoveSlider);
	slider_MaxPlayers->OnValueChanged.AddDynamic(this, &UEnteranceWidget::OnMoveSlider);
	btn_CreateRoomCancel->OnClicked.AddDynamic(this, &UEnteranceWidget::CancelCreation);
	btn_CreateRoom02->OnClicked.AddDynamic(this, &UEnteranceWidget::CreateSession);

	gameInstance = Cast<UWTBoxGameInstance>(GetGameInstance());
	if(nullptr != gameInstance)
	{
		gameInstance->searchResultDele.AddDynamic(this, &UEnteranceWidget::AddRoomSlot);
	}
}

//화면 맨 처음 Play버튼 누르면 방 찾는 위젯 나온다
void UEnteranceWidget::ClickPlay()
{
	widgetSwitcher->SetActiveWidgetIndex(1);
}

void UEnteranceWidget::CancelCreation()
{
	widgetSwitcher->SetActiveWidgetIndex(2);
}

void UEnteranceWidget::CreateSession()
{
	int32 playerCounts = FMath::RoundHalfFromZero(slider_MaxPlayers->GetValue());
	//int32 maxDurations = FMath::RoundHalfFromZero(slider_MatchDurations->GetValue());
	gameInstance->CreatewtboxSession(editText_RoomName->GetText().ToString(),playerCounts);
}

void UEnteranceWidget::OnMoveSlider(float value)
{
	int32 val = FMath::RoundHalfFromZero(value);
	text_MaxPlayersCount->SetText(FText::AsNumber(val));
}

void UEnteranceWidget::AddRoomSlot(FSessionInfo sessionInfo)
{
	USessionSlotWidget* searchSlotListWidget = CreateWidget<USessionSlotWidget>(this, searchListSlot);
	if(searchSlotListWidget != nullptr)
	{
		searchSlotListWidget->text_RoomName->SetText(FText::FromString(sessionInfo.roomName));
		searchSlotListWidget->text_GameMode->SetText(FText::FromString(TEXT("DeathMatch")));
		searchSlotListWidget->text_MemberCount->SetText(FText::FromString(FString::Printf(TEXT("%d / %d"), sessionInfo.currentPlayers, sessionInfo.maxPlayers)));
		searchSlotListWidget->text_GameTime->SetText(FText::FromString(FString::Printf(TEXT(" % d"), sessionInfo.gamePlayTime)));
		searchSlotListWidget->text_Description->SetText(FText::AsNumber(sessionInfo.ping));
		sbox_RoomList->AddChild(searchSlotListWidget);
	}
}
