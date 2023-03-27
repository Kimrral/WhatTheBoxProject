// Fill out your copyright notice in the Description page of Project Settings.


#include "BoxMainWidget.h"
#include "WhatTheBoxGameModeBase.h"
#include "Kismet/GameplayStatics.h"
#include "Components/TextBlock.h"
#include "../WhatTheBoxProjectCharacter.h"

void UBoxMainWidget::NativeConstruct()
{
	Super::NativeConstruct();

	// ���Ӹ��
	GM = Cast<AWhatTheBoxGameModeBase>(GetWorld()->GetAuthGameMode());
	// �÷��̾�
	Player = Cast<AWhatTheBoxProjectCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));

	
}

void UBoxMainWidget::PrintRemainingTime()
{
	// ���� �ð��� �ؽ�Ʈ�� ����Ѵ�.
	if (GM != nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("Fire!!!!!"));
		TXT_GameTimeSec->SetText(FText::FromString(FString::FromInt(GM->GameTimeSec)));
		TXT_GameTimeMin->SetText(FText::FromString(FString::FromInt(GM->GameTimeMin)));
	}
	
}

void UBoxMainWidget::PrintKillLog(FString Killer, FString Victim)
{
	// ų�α׸� ����Ѵ�.
	TXT_KillLog->SetText(FText::FromString(Killer + " killed " + Victim));
}

// ä����ǲ�� �Է½� ä�÷α׿� ���
void UBoxMainWidget::PrintChatLog(FString Chat)
{
	// ä�÷α׸� ����Ѵ�.
	TXT_ChatLog->SetText(FText::FromString(Chat));
}
