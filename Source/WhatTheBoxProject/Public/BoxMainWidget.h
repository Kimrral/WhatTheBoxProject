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

	// ų �α�
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UTextBlock* TXT_KillLog;

	virtual void NativeConstruct() override;
	public:
		// ���Ӹ��
		UPROPERTY(BlueprintReadWrite, Category = "GameMode")
			class AWhatTheBoxGameModeBase* GM;

		// Ÿ�̸Ӿ���
		UPROPERTY(BlueprintReadWrite, Category = "Timer")
			class ATimerActor* inGameTimer;

		// �÷��̾�
		UPROPERTY()
		class AWhatTheBoxProjectCharacter* Player;

	// ���� �ð� �ؽ�Ʈ���
	void PrintRemainingTime(int32 min, int32 sec);
	// �÷��̾� ���� ��, ų�α� ���
	void PrintKillLog(FString Killer, FString Victim);
	// ä�� ��ǲ�� ä��ġ�� ä�÷α׿� ���
	void PrintChatLog(FString Chat);
	// ä�� �Է�â�� ����Ű ������ �̺�Ʈ �Լ�
	UFUNCTION()
	void OnChatInputEnter();

	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;


	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const;
	//UFUNCTION()
	//void	UpdateKillLog(const TArray<FString>& KillLog)
};

// 	// ä�� �Է�â
// 	UPROPERTY(EditAnywhere, meta = (BindWidget))
// 	class UEditableTextBox* TXT_ChatInput;
// 
// 	// ä�÷α�
// 	UPROPERTY(EditAnywhere, meta = (BindWidget))
// 	class UTextBlock* TXT_ChatLog;