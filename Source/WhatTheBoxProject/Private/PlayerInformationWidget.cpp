// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerInformationWidget.h"
#include "Components/RadialSlider.h"
#include "AdvancedWidgets/Public/Components/RadialSlider.h"
#include "Components/TextBlock.h"
#include "WhatTheBoxProject/WhatTheBoxProjectCharacter.h"

void UPlayerInformationWidget::RefreshPlayer()
{
}

void UPlayerInformationWidget::NativeConstruct()
{
	Super::NativeConstruct();


	player = Cast<AWhatTheBoxProjectCharacter>(GetOwningPlayerPawn());

}

void UPlayerInformationWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	if(player!=nullptr)
	{
	curBulText->SetText(FText::AsNumber(player->GetAmmo()));
		player->curBulletCount=FMath::Clamp(player->curBulletCount, 0, 3);
	BulSlider->SetValue((player->GetAmmo())*0.33);
	HPSlider->SetValue((player->GetHealth())*0.33);
	}

}

