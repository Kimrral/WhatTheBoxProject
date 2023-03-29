// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "BoxMainWidget.generated.h"

/**
 * 
 */
UCLASS()
class WHATTHEBOXPROJECT_API UBoxMainWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	// ���� �ð� �� �ؽ�Ʈ
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UTextBlock* TXT_GameTimeSec;
	// ���� �ð� �� �ؽ�Ʈ
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UTextBlock* TXT_GameTimeMin;

// 	// ä�� �Է�â
// 	UPROPERTY(EditAnywhere, meta = (BindWidget))
// 	class UEditableTextBox* TXT_ChatInput;
// 
// 	// ä�÷α�
// 	UPROPERTY(EditAnywhere, meta = (BindWidget))
// 	class UTextBlock* TXT_ChatLog;

	// ų �α�
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UTextBlock* TXT_KillLog;

	virtual void NativeConstruct() override;
	public:
		// ���Ӹ��
		UPROPERTY(BlueprintReadWrite, Category = "GameMode")
			class AWhatTheBoxGameModeBase* GM;
		// �÷��̾�
		UPROPERTY()
		class AWhatTheBoxProjectCharacter* Player;

	// ���� �ð� �ؽ�Ʈ���
	void PrintRemainingTime();
	// �÷��̾� ���� ��, ų�α� ���
	void PrintKillLog(FString Killer, FString Victim);
	// ä�� ��ǲ�� ä��ġ�� ä�÷α׿� ���
	void PrintChatLog(FString Chat);
	// ä�� �Է�â�� ����Ű ������ �̺�Ʈ �Լ�
	UFUNCTION()
		void OnChatInputEnter();
	//UFUNCTION()
	//void	UpdateKillLog(const TArray<FString>& KillLog)
};
