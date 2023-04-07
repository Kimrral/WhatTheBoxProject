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
	TSharedPtr<class SWidget> GetChatInputTextObject(); // ���߿� Enter ������, ä�ÿ� ��Ŀ���ϱ� ���ؼ�.

// private:
// 	UPROPERTY(Meta = (BindWidget))
// 	class UScrollBox* ChatHistoryArea;
// 
// 	UPROPERTY(Meta = (BindWidget))
// 	class UEditableTextBox* ChatInputText;
//     
// private:
// 	// �� �Լ��� ���� ���ؼ���,
// 	// Build ���Ͽ� "UMG" ����� �߰��ϰ�, "Slate", "SlateCore" �ּ��� �����ؾ��Ѵ�.
// 	UFUNCTION()
// 	void OnChatTextCommitted(const FText& Text, ETextCommit::Type CommitMethod);
};
