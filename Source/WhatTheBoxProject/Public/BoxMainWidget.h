// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "BoxMainWidget.generated.h"


// �÷��̾� ���� ����ü ����
// USTRUCT(BlueprintType)
// struct FPlayerInfo
// {
// 	GENERATED_BODY()
// 
// 	UPROPERTY(BlueprintReadOnly)
// 	FString name;
// 	UPROPERTY(BlueprintReadOnly)
// 	float score;
// };

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
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;
public:
	// ���Ӹ��
	UPROPERTY(BlueprintReadWrite, Category = "Settings")
		class AWhatTheBoxGameModeBase* GM;
	// �÷��̾� ��Ʈ�ѷ�
	UPROPERTY(BlueprintReadWrite, Category = "Settings")
		class ABoxPlayerController* PC;
// 	// ���ӽ�����Ʈ
// 	UPROPERTY(BlueprintReadWrite, Category = "Settings")
// 	class ABoxGameStateBase* GS;
	



		// Ÿ�̸Ӿ���
		UPROPERTY(BlueprintReadWrite, Category = "Timer")
			class ATimerActor* inGameTimer;

		// �÷��̾�
		UPROPERTY()
		class AWhatTheBoxProjectCharacter* Player;
	//--------------------����ui�κ�--------------------//
	UPROPERTY(EditAnywhere, meta = (BindWidget) , Category = "Score")
	class UVerticalBox* Vertical_Rank;
	UPROPERTY(EditAnywhere, meta = (BindWidget) , Category = "Score")
	class UTextBlock* TXT_RankID1;
	UPROPERTY(EditAnywhere, meta = (BindWidget) , Category = "Score")
	class UTextBlock* TXT_RankID2;
	UPROPERTY(EditAnywhere, meta = (BindWidget) , Category = "Score")
	class UTextBlock* TXT_RankID3;
	UPROPERTY(EditAnywhere, meta = (BindWidget) , Category = "Score")
	class UTextBlock* TXT_RankID4;
	UPROPERTY(EditAnywhere, meta = (BindWidget) , Category = "Score")
	class UTextBlock* TXT_RankScore1;
	UPROPERTY(EditAnywhere, meta = (BindWidget) , Category = "Score")
	class UTextBlock* TXT_RankScore2;
	UPROPERTY(EditAnywhere, meta = (BindWidget) , Category = "Score")
	class UTextBlock* TXT_RankScore3;
	UPROPERTY(EditAnywhere, meta = (BindWidget) , Category = "Score")
	class UTextBlock* TXT_RankScore4;

	UPROPERTY()
	TArray <UTextBlock*> textblockRankIdArray;
	UPROPERTY()
	TArray <UTextBlock*> textblockRankScoreArray;
	TArray <int> tempScoreArray;

	FString myID;
	FString winnerID;

	int tempScore1;
	int tempScore2;
	int tempScore3;
	int tempScore4;

	//--------------------����ui�κ�--------------------//
// �Լ� �κ�
	// ���� �ð� �ؽ�Ʈ���
	void PrintRemainingTime(int32 min, int32 sec);
	// �÷��̾� ���� ��, ų�α� ���
	void PrintKillLog(FString Killer, FString Victim);
	// ä�� ��ǲ�� ä��ġ�� ä�÷α׿� ���
	void PrintChatLog(FString Chat);
	// ä�� �Է�â�� ����Ű ������ �̺�Ʈ �Լ�
	UFUNCTION()
	void OnChatInputEnter();

	void RankingRefresh();

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