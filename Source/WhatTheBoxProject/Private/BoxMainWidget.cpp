// Fill out your copyright notice in the Description page of Project Settings.


#include "BoxMainWidget.h"
#include "WhatTheBoxGameModeBase.h"
#include "Kismet/GameplayStatics.h"
#include "Components/TextBlock.h"
#include "Components/EditableTextBox.h"
#include "../WhatTheBoxProjectCharacter.h"
#include "BoxGameMode.h"
#include "Net/UnrealNetwork.h"

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
		GEngine->AddOnScreenDebugMessage(-1, 3, FColor::Green, FString("oiio"), true, FVector2D(1.2f));
		TXT_GameTimeSec->SetText(FText::FromString(FString::FromInt(GM->GameTimeSec)));
		TXT_GameTimeMin->SetText(FText::FromString(FString::FromInt(GM->GameTimeMin)));
		// ���� GameTimeSec�� 10���� ������ GameTimeSec �տ� 0�� �ٿ��ش�.
		if (GM->GameTimeSec < 10)
		{
			TXT_GameTimeSec->SetText(FText::FromString("0" + FString::FromInt(GM->GameTimeSec)));
		}
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
//	TXT_ChatLog->SetText(FText::FromString(Chat));
}

void UBoxMainWidget::OnChatInputEnter()
{
	// ä�� �Է�â���� �Է��� �ؽ�Ʈ ��������
//	FString Chat = TXT_ChatInput->GetText().ToString();

	// ä�÷α׿� ���
//	PrintChatLog(Chat);
}

void UBoxMainWidget::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	// Replicate GM variable
	DOREPLIFETIME(UBoxMainWidget, GM);
}

//void UBoxMainWidget::UpdateKillLog(const TArray<FString>& KillLog)
//{
//	FString KillLogText;
//	for (const FString& KillMessage : KillLog)
//	{
//		KillLogText += KillMessage + TEXT("\n");
//	}
//	TXT_KillLog->SetText(FText::FromString(KillLogText));
//}
