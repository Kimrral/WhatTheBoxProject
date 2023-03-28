// Fill out your copyright notice in the Description page of Project Settings.


#include "SearchWidget.h"

#include "EnteranceWidget.h"
#include "Components/Button.h"
#include "Components/EditableText.h"
#include "Components/WidgetSwitcher.h"

void USearchWidget::NativeConstruct()
{
	Super::NativeConstruct();

	editText_RoomName->SetText(FText::FromString(""));

	btn_BackToMenu->OnClicked.AddDynamic(this, &USearchWidget::BackToMenu);
	btn_QuickPlay->OnClicked.AddDynamic(this, &USearchWidget::QuickPlay);
	btn_CreateRoom->OnClicked.AddDynamic(this, &USearchWidget::CreateRoom);

}

void USearchWidget::BackToMenu()
{
	enteranceWidget->widgetSwitcher->SetActiveWidgetIndex(0);
}

void USearchWidget::QuickPlay()
{
}

void USearchWidget::CreateRoom()
{
}
