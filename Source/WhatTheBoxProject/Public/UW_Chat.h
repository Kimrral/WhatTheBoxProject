// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "UW_Chat.generated.h"

/**
 * 
 */
UCLASS()
class WHATTHEBOXPROJECT_API UUW_Chat : public UUserWidget
{
	GENERATED_BODY()
public:
	virtual void NativeConstruct() override;
    
public:
	void AddChatMessage(const FString& Message);
	FText GetChatInputTextMessage();
	TSharedPtr<class SWidget> GetChatInputTextObject(); // 나중에 Enter 누르면, 채팅에 포커싱하기 위해서.

// private:
// 	UPROPERTY(Meta = (BindWidget))
// 	class UScrollBox* ChatHistoryArea;
// 
// 	UPROPERTY(Meta = (BindWidget))
// 	class UEditableTextBox* ChatInputText;
//     
// private:
// 	// 이 함수를 쓰기 위해서는,
// 	// Build 파일에 "UMG" 모듈을 추가하고, "Slate", "SlateCore" 주석을 해제해야한다.
// 	UFUNCTION()
// 	void OnChatTextCommitted(const FText& Text, ETextCommit::Type CommitMethod);
};
