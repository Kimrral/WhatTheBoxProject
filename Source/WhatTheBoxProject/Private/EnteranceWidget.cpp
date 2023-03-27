// Fill out your copyright notice in the Description page of Project Settings.


#include "EnteranceWidget.h"

#include "Components/Button.h"
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
