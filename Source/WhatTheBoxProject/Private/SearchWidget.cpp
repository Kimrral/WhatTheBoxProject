// Fill out your copyright notice in the Description page of Project Settings.


#include "SearchWidget.h"

#include "EnteranceWidget.h"
#include "Components/Button.h"
#include "Components/EditableText.h"
#include "Components/WidgetSwitcher.h"
#include "Kismet/GameplayStatics.h"
#include "WTBoxGameInstance.h"

void USearchWidget::NativeConstruct()
{
	Super::NativeConstruct();

	editText_RoomName->SetText(FText::FromString(""));

	btn_BackToMenu->OnClicked.AddDynamic(this, &USearchWidget::BackToMenu);
	btn_QuickPlay->OnClicked.AddDynamic(this, &USearchWidget::QuickPlay);
	btn_CreateRoom->OnClicked.AddDynamic(this, &USearchWidget::CreateRoom);

}

void USearchWidget::QuickPlay()
{
	UGameplayStatics::OpenLevel(GetWorld(), FName("KHJTestMap"));
}

//방 이름 적고 이 버튼을 누르면 만든 방으로 들어간다
void USearchWidget::CreateRoom()
{
	//int32 playerCounts = FMath::RoundHalfFromZero(GetValue());
	gameInstance->CreatewtboxSession(editText_RoomName->GetText().ToString());
}

void USearchWidget::BackToMenu()
{
	enteranceWidget->widgetSwitcher->SetActiveWidgetIndex(0);
}
