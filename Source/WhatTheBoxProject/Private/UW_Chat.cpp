// Fill out your copyright notice in the Description page of Project Settings.


#include "UW_Chat.h"
#include "Components/TextBlock.h"
#include "Components/ScrollBox.h"
#include "Components/EditableTextBox.h"
#include "Kismet/GameplayStatics.h"

void UUW_Chat::NativeConstruct()
{
	Super::NativeConstruct();

	// 채팅 입력창에 포커싱
//	ChatInputText->OnTextCommitted.AddDynamic(this, &UUW_Chat::OnChatTextCommitted);
}

void UUW_Chat::AddChatMessage(const FString& Message)
{
}

FText UUW_Chat::GetChatInputTextMessage()
{
	return FText();
}

TSharedPtr<class SWidget> UUW_Chat::GetChatInputTextObject()
{
	return TSharedPtr<class SWidget>();
}

// void UUW_Chat::OnChatTextCommitted(const FText& Text, ETextCommit::Type CommitMethod)
// {
// }
