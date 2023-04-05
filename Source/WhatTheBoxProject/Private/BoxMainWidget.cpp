// Fill out your copyright notice in the Description page of Project Settings.


#include "BoxMainWidget.h"
#include "WhatTheBoxGameModeBase.h"
#include "Kismet/GameplayStatics.h"
#include "Components/TextBlock.h"
#include "Components/EditableTextBox.h"
#include "Components/VerticalBox.h"
#include "../WhatTheBoxProjectCharacter.h"
#include "BoxGameMode.h"
#include "Net/UnrealNetwork.h"
#include "TimerActor.h"

void UBoxMainWidget::NativeConstruct()
{
	Super::NativeConstruct();

	// ���Ӹ��
	GM = Cast<AWhatTheBoxGameModeBase>(GetWorld()->GetAuthGameMode());

	// ����Ÿ�̸Ӿ���
	inGameTimer = Cast<ATimerActor>(UGameplayStatics::GetActorOfClass(GetWorld(), ATimerActor::StaticClass()));

	// �÷��̾�
	Player = Cast<AWhatTheBoxProjectCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
}

void UBoxMainWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	/*UE_LOG(LogTemp, Warning, TEXT("%s"), GetWorld()->GetAuthGameMode() != nullptr ? *FString("HAS") : *FString("None"));*/

	// 	AWhatTheBoxGameModeBase* gm = Cast< AWhatTheBoxGameModeBase>(GetWorld()->GetAuthGameMode());

	if (inGameTimer != nullptr && this != nullptr)
	{
		inGameTimer->Server_UpdateTimerUI();
	}
}

void UBoxMainWidget::PrintRemainingTime(int32 min, int32 sec)
{
	// ���� �ð��� �ؽ�Ʈ�� ����Ѵ�.

	TXT_GameTimeMin->SetText(FText::AsNumber(min));
	TXT_GameTimeSec->SetText(FText::AsNumber(sec));

	if (sec < 10)
	{
		TXT_GameTimeSec->SetText(FText::FromString("0" + FString::FromInt(sec)));
	}

// 	if (inGameTimer != nullptr)
// 	{
// 		
// 		// ���� GameTimeSec�� 10���� ������ GameTimeSec �տ� 0�� �ٿ��ش�.
// 		if (inGameTimer->GameTimeSec < 10)
// 		{
// 			TXT_GameTimeSec->SetText(FText::FromString("0" + FString::FromInt(inGameTimer->GameTimeSec)));
// 		}
// 	}

}

void UBoxMainWidget::PrintKillLog(FString Killer, FString Victim)
{
	// ų�α׸� ����Ѵ�.
	TXT_KillLog->SetText(FText::FromString(Killer + " killed " + Victim));
}

// ä����ǲ�� �Է½� ä�÷α׿� ���
void UBoxMainWidget::PrintChatLog(FString Chat)
{

}

void UBoxMainWidget::OnChatInputEnter()
{

}

void UBoxMainWidget::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	// Replicate GM variable
	DOREPLIFETIME(UBoxMainWidget,inGameTimer);
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
