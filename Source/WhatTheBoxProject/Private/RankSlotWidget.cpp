// Fill out your copyright notice in the Description page of Project Settings.


#include "RankSlotWidget.h"
#include "Components/TextBlock.h"


void URankSlotWidget::NativeConstruct()
{
	Super::NativeConstruct();

	text_pingNumber->SetText(FText::FromString(("")));
	text_playerName->SetText(FText::FromString(("")));
	text_finalScore->SetText(FText::FromString(""));
	text_finalScore->SetText(FText::FromString(""));
	text_finalDeaths->SetText(FText::FromString(""));
}
