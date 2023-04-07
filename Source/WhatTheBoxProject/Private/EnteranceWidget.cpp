// Fill out your copyright notice in the Description page of Project Settings.


#include "EnteranceWidget.h"

//#include "SearchWidget.h"
#include "Components/TextBlock.h"
#include "Components/Slider.h"
#include "Components/EditableText.h"
#include "Components/Button.h"
#include "SessionSlotWidget.h"
#include "Components/ScrollBox.h"
#include "Components/WidgetSwitcher.h"
#include "WTBoxGameInstance.h"
#include "Kismet/GameplayStatics.h"
#include "EnteranceWidget.h"


void UEnteranceWidget::NativeConstruct()
{
	Super::NativeConstruct();

	editText_PlayerName->SetText(FText::FromString(""));

	btn_BackToMenu->OnClicked.AddDynamic(this, &UEnteranceWidget::BackToMenu);
	btn_QuickPlay->OnClicked.AddDynamic(this, &UEnteranceWidget::QuickPlay);
	btn_CreateRoom->OnClicked.AddDynamic(this, &UEnteranceWidget::ClickCreateRoom);

	btn_Play->OnClicked.AddDynamic(this, &UEnteranceWidget::ClickPlay);
	editText_RoomName->SetText(FText::FromString(""));
	text_MatchDurations->SetText(FText::FromString("1"));
	text_MaxPlayersCount->SetText(FText::FromString("2"));
	slider_MatchDurations->OnValueChanged.AddDynamic(this, &UEnteranceWidget::OnMoveDurationSlider);
	slider_MaxPlayers->OnValueChanged.AddDynamic(this, &UEnteranceWidget::OnMovePlayerSlider);
	btn_CreateRoomCancel->OnClicked.AddDynamic(this, &UEnteranceWidget::CancelCreation);
	btn_CreateRoom02->OnClicked.AddDynamic(this, &UEnteranceWidget::CreateSession);

	gameInstance = Cast<UWTBoxGameInstance>(GetGameInstance());
	if(nullptr != gameInstance)
	{
		gameInstance->searchResultDele.AddDynamic(this, &UEnteranceWidget::AddRoomSlot);
	}
}

//화면 맨 처음 Play버튼 누르면 방 찾는 위젯 나온다
//근데 이제 방 리스트도 떠야해
void UEnteranceWidget::ClickPlay()
{

	widgetSwitcher->SetActiveWidgetIndex(1);
	
	RefreshList();
	
}

void UEnteranceWidget::QuickPlay()
{
	if (!(editText_PlayerName->GetText().IsEmpty()))
	{
		gameInstance->sessionID = FName(*editText_PlayerName->GetText().ToString());
		UGameplayStatics::OpenLevel(GetWorld(), FName("KHJTestMap"));
	}
}

void UEnteranceWidget::ClickCreateRoom()
{
	if(!(editText_PlayerName->GetText().IsEmpty()))
	{
		widgetSwitcher->SetActiveWidgetIndex(2);
		gameInstance->sessionID = FName(*editText_PlayerName->GetText().ToString());
	}
	
}

void UEnteranceWidget::BackToMenu()
{
	widgetSwitcher->SetActiveWidgetIndex(0);
}

void UEnteranceWidget::AddRoomSlot(FSessionInfo sessionInfo)
{
	USessionSlotWidget* searchSlotListWidget = CreateWidget<USessionSlotWidget>(this, searchListSlot);
	if (searchSlotListWidget != nullptr)
	{
		searchSlotListWidget->text_RoomName->SetText(FText::FromString(sessionInfo.roomName));
		searchSlotListWidget->text_GameMode->SetText(FText::FromString("DeathMatch"));
		searchSlotListWidget->text_MemberCount->SetText(FText::FromString(FString::Printf(TEXT("%d / %d"), sessionInfo.currentPlayers, sessionInfo.maxPlayers)));
		searchSlotListWidget->text_GameTime->SetText(FText::FromString(FString::Printf(TEXT("%d"), sessionInfo.gamePlayTime)));
		searchSlotListWidget->text_Description->SetText(FText::AsNumber(sessionInfo.ping));
		searchSlotListWidget->index = sessionInfo.index;
		sbox_RoomList->AddChild(searchSlotListWidget);
	}
}

/*Room Creation Widget에서 Cancel버튼 눌렀을 때*/
void UEnteranceWidget::CancelCreation()
{
	widgetSwitcher->SetActiveWidgetIndex(1);
}

/*Room Creation Widget에서 CreateRoom버튼 눌렀을 때*/
void UEnteranceWidget::CreateSession()
{
	if(gameInstance != nullptr)
	{
		//방 이름: editText_RoomName->GetText().ToString()
		//플레이어 이름:editText_PlayerName
		//플레이어 수:
		int32 playerCounts = FMath::RoundHalfFromZero(slider_MaxPlayers->GetValue());
		//플레이 시간:
		int32 maxDurations = FMath::RoundHalfFromZero(slider_MatchDurations->GetValue());
		gameInstance->CreatewtboxSession(editText_RoomName->GetText().ToString(), playerCounts, maxDurations);
	}
	
}

void UEnteranceWidget::OnMovePlayerSlider(float value)
{
	int32 val = FMath::RoundHalfFromZero(value);
	text_MaxPlayersCount->SetText(FText::AsNumber(val));
}

void UEnteranceWidget::OnMoveDurationSlider(float value)
{
	int32 val = FMath::RoundHalfFromZero(value);
	text_MatchDurations->SetText(FText::AsNumber(val));
}

void UEnteranceWidget::RefreshList()
{
	sbox_RoomList->ClearChildren();
	gameInstance->FindwtbSessions();
}

